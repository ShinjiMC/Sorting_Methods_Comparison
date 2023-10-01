import matplotlib.pyplot as plt
import numpy as np
import re

class CustomLineStyle:
    def __init__(self, width, color):
        self.width = width
        self.color = color

def add_commas(value, _):
    return "{:,}".format(value)

def read_from_file(filename):
    with open(filename, 'r') as file:
        data = file.read()
    return data

def get_max_value(values):
    max_val = -1.0
    for row in values:
        for val in row:
            if val > max_val:
                max_val = val
    return max_val

def plot_data(values, sort):
    _, ax = plt.subplots()

    ax.set_title("Comparing Methods of Sorting")
    ax.set_xlabel("Size of Data")
    ax.set_ylabel("Delay Time")
    ax.get_yaxis().set_major_formatter(plt.FuncFormatter(add_commas))

    Xsort = ["0", "5", "10", "50", "100", "250", "500", "1000", "1500", "2500", "5000", "7500", "10000"]
    xticks = np.arange(len(Xsort))
    ax.set_xticks(xticks)
    ax.set_xticklabels(Xsort)
    maxY = get_max_value(values)
    y_ticks = []
    i = 0.0
    while i <= maxY:
        tick_value = i
        if maxY > 100:
            y_ticks.append(tick_value)
            tick_value += 20.0
        elif maxY > 50:
            y_ticks.append(tick_value)
            tick_value += 10.0
        elif maxY > 4:
            y_ticks.append(tick_value)
            tick_value += 1.0
        elif maxY > 1:
            y_ticks.append(tick_value)
            tick_value += 0.1
        elif maxY > 0.03:
            y_ticks.append(tick_value)
            tick_value += 0.01
        elif maxY > 0.02:
            y_ticks.append(tick_value)
            tick_value += 0.005
        else:
            y_ticks.append(tick_value)
            tick_value += 0.001
        i = tick_value

    ax.set_yticks(y_ticks)

    line_styles = [
        CustomLineStyle(width=1, color='red'),
        CustomLineStyle(width=1, color='blue'),
        CustomLineStyle(width=1, color='green'),
        CustomLineStyle(width=1, color='purple'),
        CustomLineStyle(width=1, color='orange'),
        CustomLineStyle(width=1, color='teal'),
        CustomLineStyle(width=1, color='olive'),
        CustomLineStyle(width=1, color='brown'),
        CustomLineStyle(width=1, color='navy'),
        CustomLineStyle(width=1, color='darkgreen'),
        CustomLineStyle(width=1, color='darkviolet')
    ]

    for i, vals in enumerate(values):
        pts = np.array([(j, val) for j, val in enumerate(vals)])

        line_style = line_styles[i]

        ax.plot(pts[:, 0], pts[:, 1], label=sort[i], linewidth=line_style.width, color=line_style.color)

    ax.legend(loc='upper left')
    ax.grid()

    plt.gcf().set_size_inches(7, 6)
    plt.savefig("Lineal.png", dpi=300, bbox_inches='tight', format='png')
    plt.show()
    
def split_log_line(text):
    parts = re.split(r'\s+', text)
    numbers = []
    for part in parts:
        part = part.strip()
        if part:
            number = float(part)
            numbers.append(number)
    return numbers

def main():
    sorts = ["Bubble", "Heap", "Insertion", "Selection", "Shell", "Merge", "Quick"]
    values = []
    for sort in sorts:
        filename = f"./Lineal/{sort}"
        try:
            with open(filename, 'r') as file:
                data = file.read()
                values.append(data)
        except Exception as e:
            print(f"Error al leer el archivo {sort}: {e}")
            continue

    values_x = [split_log_line(value) for value in values]
    plot_data(values_x, sorts)

if __name__ == "__main__":
    main()
