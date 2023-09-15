import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

names = ['Stream-dataflow', 'C-O3', 'C-O0', 'Naive-pipe', 'Naive-pipe-off', 'Python']
values = [0.059, 0.19, 0.95, 1.55, 10.87, 40]

width = 0.2
blue = '#1f77b4'
orange = '#ff7f0e'
colors = [orange, blue, blue, orange, orange, blue]
ax = plt.barh(names, values, width, color = colors,  edgecolor = 'black')

# Value at the end of the bar.
plt.bar_label(ax, [0.059, 0.19, 0.95, 1.55, 10.87, 40], padding=3)

# Legend.
orange_patch = mpatches.Patch(facecolor = orange, label='HLS (xc7a200tfbg484-1)', edgecolor = 'black')
blue_patch = mpatches.Patch(facecolor = blue, label='SW execution (i5-8265U)', edgecolor = 'black')
plt.legend(ax, handles = [blue_patch, orange_patch], loc = "lower right")

plt.xscale('log')
plt.xlim(10E-3, 10E1)
plt.gca().xaxis.grid(True)
plt.xlabel('Time (ms)')


plt.title('Prediction latency')
# Better resolution and fit the content.
plt.savefig('plot.png', dpi=300, bbox_inches='tight')
