import pandas as pd
import matplotlib.pyplot as plt
import matplotlib

# Using 'Agg' because we will save the diagram in a PNG file
matplotlib.use('Agg')

# Loading data from the CSV file
df = pd.read_csv("parallel_execution_times.csv")

# # Filtering for parallel row algorithm
# subset = df[df["Is_row_or_collumn"] == 0]

# # Grouping by thread_num and matrix_size to compute the mean execution time
# summary = subset.groupby(["matrix_size", "thread_num"])["Execution_time"].mean().reset_index()

# # Plotting
# plt.figure(figsize=(10, 6))

# # Iterating over unique matrix sizes to create separate lines
# for matrix_size in summary["matrix_size"].unique():
#     data = summary[summary["matrix_size"] == matrix_size]
#     plt.plot(
#         data["thread_num"], data["Execution_time"], marker='o', label=f"Matrix Size = {matrix_size}"
#     )

# # Adding labels, title, and legend
# plt.xlabel("Number of Threads")
# plt.ylabel("Mean Execution Time (seconds)")
# plt.title("Execution Time for Parallel Row Algorithm")
# plt.grid()
# plt.legend()

# # Save the plot as a PNG file
# plt.savefig("parallelbyRow_plot.png")

subset = df[df["Is_row_or_collumn"] == 1]

summary = subset.groupby(["matrix_size","thread_num"])["Execution_time"].mean().reset_index()


# Iterating over unique matrix sizes to create separate lines
for matrix_size in summary["matrix_size"].unique():
    data = summary[summary["matrix_size"] == matrix_size]
    plt.plot(
        data["thread_num"], data["Execution_time"], marker='o', label=f"Matrix Size = {matrix_size}"
    )

# Adding labels, title, and legend
plt.xlabel("Number of Threads")
plt.ylabel("Mean Execution Time (seconds)")
plt.title("Execution Time for Parallel Collumn Algorithm")
plt.grid()
plt.legend()
plt.savefig("parallelbyCollumn_plot.png")


import pandas as pd
import matplotlib.pyplot as plt
import matplotlib

# Using 'Agg' backend because we will save the diagram in a PNG file
matplotlib.use('Agg')

# Loading the data
df = pd.read_csv("serial_execution_times.csv")

# Filtering the data
subset = df[df["Is_row_or_collumn"] == 0]  # Using subset for serial row algorithm

# Grouping by matrix size and computing mean execution time
summary = subset.groupby(["matrix_size"])["Execution_time"].mean().reset_index()

# Plotting
plt.figure(figsize=(10, 6))
plt.plot(summary["matrix_size"], summary["Execution_time"], marker='o', label="Serial by Row")

# Adding labels, title, and legend
plt.xlabel("Matrix Size")
plt.ylabel("Mean Execution Time (seconds)")
plt.title("Execution Time for Serial Collumn Algorithm")
plt.grid()
plt.legend()

# Saving the plot as a PNG file
plt.savefig("Serial_byRow.png")




