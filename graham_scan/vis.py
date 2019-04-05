from matplotlib import pyplot as plt
import pandas as pd
import numpy as np

df = pd.read_csv("example.csv")
df=df.values

x=df[:,0]
y=df[:,1]
plt.scatter(x,y)
discard= df[:,-1]
x_accept = x[discard==0]
y_accept = y[discard==0]

x_reject = x[discard==1]
y_reject = y[discard==1]


plt.plot(x_accept,y_accept,c="b")
plt.scatter(x_reject,y_reject,c='r')
plt.show
