import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits import mplot3d

data_df = pd.read_csv('acceleration_data_test2.csv')

acceleration_df = data_df[['Time',' Ax', ' Ay', ' Az']].copy()
print(data_df.head())

#gyroscope_df = data_df['Gx ', 'Gy ', 'Gz ']

x = acceleration_df[" Ax"].to_numpy()
y = acceleration_df[" Ay"].to_numpy()
z = acceleration_df[" Az"].to_numpy()

# Creating figure
# fig = plt.figure(figsize = (10, 7))
fig = plt.figure()
ax = plt.axes(projection ="3d")
 
# Creating plot
ax.scatter3D(x, y, z)
 
# show plot
plt.show()

plt.title("Sample Acceleration Data")

# plt.show()

# print(acceleration_matrix)