import pandas as pd
import matplotlib.pyplot as plt
import matplotlib

# Use the Agg backend for non-GUI environments
matplotlib.use('Agg')

# Load data
df = pd.read_csv("execution_times.csv")

# Filter data for a specific grid size
subset = df[df["Grid_Size"] == 4096]

# Group by Num_Threads and calculate the mean Execution_Time
summary = subset.groupby("Num_Threads")["Execution_Time"].mean()

# Plot the summarized execution time vs. number of threads
plt.plot(summary.index, summary.values, marker='o', label="Grid Size = 4096")
plt.xlabel("Number of Threads")
plt.ylabel("Mean Execution Time (seconds)")
plt.title("Execution Time for Grid Size 4096")
plt.grid()
plt.legend()

# Save the plot as a PNG file
plt.savefig("execution_time_plot.png")
