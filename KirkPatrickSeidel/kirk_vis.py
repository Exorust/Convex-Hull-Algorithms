from matplotlib import pyplot as plt
import pandas as pd

df_input = pd.read_csv("input.csv")
df_output = pd.read_csv("example.csv")

df_input = df_input.values
df_output = df_output.values

x_input=df_input[:, 0]
x_output=df_output[:, 0]

y_input = df_input[:, 1]
y_output = df_output[:, 1]

plt.plot(x_output, y_output, c='b')
plt.scatter(x_input,y_input,c='r')
plt.scatter(x_output, y_output, c='b')
plt.show()