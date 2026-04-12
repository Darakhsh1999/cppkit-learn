import os
import numpy as np
import pandas as pd
from perf_timer import Timer
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error


timer = Timer()

# Load data
timer.start()
data = pd.read_csv(os.path.join("..","data","regression_data.csv"))
data_load_time = timer.stop()

y = data["target"]
X = data.drop(columns="target", axis=1)

# Train test splits
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=1999)

# Fit model
timer.start()
model = LinearRegression()
model.fit(X_train, y_train)
fit_time = timer.stop()

# Predict on test data
timer.start()
y_pred = model.predict(X_test)
inference_time = timer.stop()

# Calculate score
mse = mean_squared_error(y_test,y_pred)

# Result logging
print(f"Data loading time: {1000*data_load_time:.4f} ms")
print(f"Fit time: {1000*fit_time:.4f} ms")
print(f"Inference time: {1000*inference_time:.4f} ms")
print(f"MSE = {mse:.3f}")