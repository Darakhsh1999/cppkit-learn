#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include <time.h>

class KMeansClustering {

    private:
        int m_K;
        const char* m_init_method;
        int m_max_iter;
        float m_tol;
        float* S = nullptr;
        float* D = nullptr; 

    public:

        KMeansClustering(int K, const char* init_method, int max_iter = 300, float tol = 1e-3f)
            : m_K(K),  m_init_method(init_method), m_max_iter(max_iter), m_tol(tol) {}
        
        ~KMeansClustering() {
            if (S != nullptr)
                delete[] S; 
        }

        float* get_centroid() {return S;}
        
        void fit(float* X, int N, int n_dims) { // X (N,n_dims)

            // Initialize memory for fit
            int* y = new int[N]; // (N,)
            int* I_vec = new int[m_K]; // (K,)
            float* C_vec = new float[m_K*n_dims]; // (K,n_dims)
            S = new float[m_K*n_dims]; // centroids (K,n_dims)
            D = new float[N*m_K]; // (N,K)

            // Initialize centroids
            initialize_centroid(X, N, n_dims);

            // Run main iteration
            for (int iter = 0; iter < m_max_iter; iter++) {

                // Calculate distance to centroids
                for (int i = 0; i < N; i++) {
                    for (int k = 0; k < m_K; k++) {

                        float L2 = 0.0f;
                        for (int d = 0; d < n_dims; d++) { 
                            float diff = (X[i*n_dims + d] - S[k*n_dims + d]);
                            L2 +=  diff*diff;
                        }

                        D[i*m_K + k] = sqrtf(L2);
                    }
                }


                // Classify closest centroid
                for (int i = 0; i < N; i++) {
                    int min_idx = 0;
                    float min_dist = D[i*m_K];
                    for (int k = 1; k < m_K; k++) {
                        if (D[i*m_K + k] < min_dist) {
                            min_dist = D[i*m_K + k];
                            min_idx  = k;
                        }
                    }
                    y[i] = min_idx;
                }

                // Update centroids
                memset(C_vec, 0, m_K*n_dims*sizeof(float)); // reset to 0 for each iteration
                memset(I_vec, 0, m_K*sizeof(int)); // reset to 0 for each iteration
                for (int i = 0; i < N; i++) { 
                    I_vec[y[i]]++;
                    for (int d = 0; d < n_dims; d++)
                        C_vec[y[i]*n_dims + d] += X[i*n_dims + d];
                }
                for (int k = 0; k < m_K; k++) { // normalize w.r.t number of points
                    for (int d = 0; d < n_dims; d++) {
                        C_vec[k*n_dims + d] /= I_vec[k];
                        S[k*n_dims + d] = C_vec[k*n_dims + d];
                    }
                }

                // TODO Check break condition

            }
        
        // TODO Calculate Intra cluster distances

        // free memory
        delete[] y;
        delete[] I_vec;
        delete[] C_vec;
        delete[] D;

        }
    
    private:
        void initialize_centroid(float* X, int N, int n_dims) {

            if (strcmp(m_init_method, "random") == 0) {
                std::cout << "Initialized centroids using random initialization" << std::endl;
                for (int k = 0; k < m_K; k++) {
                    for (int d = 0; d < n_dims; d++)
                        S[k*n_dims + d] = (float) (rand() / (float) RAND_MAX);
                }
                return;
            } else if (strcmp(m_init_method, "kmeans++") == 0) {
                std::cout << "Initialized centroids using kmeans++ algorithm" << std::endl;

                bool skip_point;
                int* chosen_centroids = new int[m_K]; 
                memset(chosen_centroids, 0, m_K*sizeof(int)); 
                
                // First centroid as first data point
                for (int d = 0; d < n_dims; d++) 
                    S[d] = X[d];

                // Pick remaining centroids using max distance
                for (int k = 1; k < m_K; k++) {

                    float max_dist_global = 0.0f;
                    int max_idx_global = 0;

                    // Calculate distances
                    for (int i = 0; i < N; i++) {

                        skip_point = false;

                        // skip if data is already chosen 
                        for (int q = 0; q < m_K; q++)
                            if (i == chosen_centroids[q]) {
                                skip_point = true;
                                break;
                            }
                        if (skip_point) {
                            std::cout << "skipped point i = " << i << std::endl;
                            continue;
                        }                        

                        float min_dist = INFINITY;

                        // Distance between data point and chosen centroids 
                        for (int k2 = 0; k2 < k; k2++) {
                            float L2 = 0.0f;
                            for (int d = 0; d < n_dims; d++) { 
                                float diff = (X[i*n_dims + d] - S[k2*n_dims + d]);
                                L2 += diff*diff;
                            }
                            if (L2 < min_dist)
                                min_dist = L2;
                        }

                        // Update global min distance
                        if (max_dist_global < min_dist) {
                            max_dist_global = min_dist;
                            max_idx_global = i;
                        }
                        
                    }

                    // Write new centroid 
                    for (int d = 0; d < n_dims; d++)
                        S[k*n_dims + d] = X[max_idx_global*n_dims + d];
                    
                    chosen_centroids[k] = max_idx_global; // append new centroid
                    std::cout << "appended data point idx = " << max_idx_global << std::endl;

                } 

                delete[] chosen_centroids;
                return;

            } else {
                std::cout << "Invalid init method" << std::endl;
                exit(-1);
            }
        }

};


int main() {

    const float PI = 3.141592653589793238463;
    float angle; 
    float x;
    float deviation = 0.05f;
    int N = 100;
    int n_dims = 2;
    int n_categories = 5;
    int K = 5;
    int max_iter = 0;
    float * X = new float[N*n_dims]; // (N,n_dims)

    srand(time(NULL));

    // Initialize X
    for (int i = 0; i < N; i++) {
        angle = 2.0f*PI*(rand() % n_categories)/ (float) n_categories;
        for (int j = 0; j < n_dims; j++) {
            if (j % 2 == 0) { // x-cord
                x = cosf(angle);
            } else { // y-cord
                x = sinf(angle);
            }
            X[i*n_dims + j] = x - deviation + (float) deviation*(rand() / (float) RAND_MAX);
        }
    }


    // Define classifier and fit
    KMeansClustering clf(K, "random", max_iter, 0.01f);
    clf.fit(X, N, n_dims);


    // Write data and centroids to memory
    FILE* fptr = fopen("X_data.bin", "wb");
    fwrite((const void*) X, sizeof(float), N*n_dims, fptr);
    fclose(fptr);
    fptr = fopen("centroid_data.bin", "wb");
    fwrite((const void*) clf.get_centroid(), sizeof(float), K*n_dims, fptr);
    fclose(fptr);

    delete[] X;
    std::cout << "Code finished without any errors" << std::endl;
    return 0;
}