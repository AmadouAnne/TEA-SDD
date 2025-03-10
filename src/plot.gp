# Set the terminal type (PNG image, optional for exporting to a file)
set terminal pngcairo enhanced font 'Arial,12'

# Output file (if exporting to a PNG image)
set output 'plot_temps_exec_redblack.png'

# Title and labels
set title "Temps d'insertion dans les différents arbres"
set xlabel "Nombre d'éléments"
set ylabel "Temps d'insertion (ms)"

# Grid settings
set grid

# Key (legend) positioning
set key inside right top

# Plot data
plot "data_rb.dat" using 1:2 with linespoints title "Temps d'insertion arbre Rouge et Noir", \
	"data_avl.dat" using 1:2 with linespoints title "Temps d'insertion arbre AVL"
