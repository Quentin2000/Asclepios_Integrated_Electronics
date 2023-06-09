import sys
import pandas as pd
import matplotlib.pyplot as plt

# Check if the filename argument is provided
if len(sys.argv) < 2:
    print("Please provide the filename as an argument.")
    sys.exit(1)

# Get the filename from the command-line argument
filename = sys.argv[1]
extension = ".txt"
filename = filename + "/" + filename + extension

single_window_plots = 1

try:
    # Read the sensor file
    sensor_data = pd.read_csv(filename, delimiter=';', skiprows=2)

    # Extract the column names from the file
    column_names = sensor_data.columns.tolist()

    # Remove leading/trailing whitespaces from column names
    column_names = [name.strip() for name in column_names]

    print("column_names :", column_names)

    # Create a new DataFrame with separated values
    separated_data = pd.DataFrame(sensor_data.values, columns=column_names)

    # Save the separated data to an Excel file
    excel_filename = filename.split('.')[0] + '.xlsx'
    separated_data.to_excel(excel_filename, index=False)

    print(f"Excel file '{excel_filename}' has been generated.")

    # Convert Timestamp column to datetime format
    # sensor_data['Timestamp [s]'] = pd.to_datetime(sensor_data['Timestamp [s]'], unit='s')


    # Set the Timestamp column as the index
    # sensor_data.set_index('Timestamp [s]', inplace=True)

    timestamps = sensor_data["Timestamp [s]"]

    # Get the column names excluding the timestamps column
    column_names = sensor_data.columns[1:]

    if single_window_plots:

        # Calculate the number of figures and rows
        num_figures = len(column_names)
        num_rows = (num_figures + 2) // 3  # Round up to the nearest integer

        # Set up subplots
        fig, axes = plt.subplots(num_rows, 3, sharex=True, figsize=(12, 6))
        plt.subplots_adjust(hspace=0.5, wspace=0.5)  # Adjust the spacing

        # Flatten the axes array for easier iteration
        axes = axes.flatten()

        # Iterate over the columns and plot them on separate subplots
        for i, column in enumerate(column_names):
            values = sensor_data[column]
            axes[i].plot(timestamps, values)
            axes[i].set_ylabel(column)
                
            # Hide empty subplots if there are fewer columns than subplots
            if i >= num_figures:
                axes[i].axis("off")

        # Remove any unused subplots
        for j in range(num_figures, len(axes)):
            fig.delaxes(axes[j])

        # Set the x-axis label and title for the overall plot
        axes[-2].set_xlabel("Timestamp [s]")
        fig.suptitle("Sensors data over time")

    else:

        # Plot graph for each column
        for column in column_names:
            plt.plot(timestamps, sensor_data[column])
            plt.xlabel("Timestamp [s]")
            plt.ylabel(column)
            plt.title(column and " values over time")

    # Save the graph as an image file (e.g., PNG, JPEG, PDF)
    graph_filename = filename.split('.')[0] + '.png'
    plt.savefig(graph_filename)
    plt.grid(True)
    plt.show()

    print(f"Graphs generated.")    

except FileNotFoundError:
    print("File not found. Please provide a valid filename.")
