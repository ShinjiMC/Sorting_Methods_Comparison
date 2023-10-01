package main

import (
	"fmt"
	"image/color"
	"os"
	"regexp"
	"strconv"
	"strings"

	"gonum.org/v1/plot"
	"gonum.org/v1/plot/plotter"
	"gonum.org/v1/plot/vg"
	"gonum.org/v1/plot/vg/draw"
)

type CustomLineStyle struct {
	Width vg.Length
	Color color.RGBA
}

func (c CustomLineStyle) ConvertToLineStyle() draw.LineStyle {
	return draw.LineStyle{
		Width:    c.Width,
		Color:    c.Color,
		Dashes:   []vg.Length{},
		DashOffs: 0,
	}
}

type commaTicks struct{}

func addCommas(s string) string {
	rev := ""
	n := 0
	for i := len(s) - 1; i >= 0; i-- {
		rev += string(s[i])
		n++
		if n%3 == 0 {
			rev += ","
		}
	}
	s = ""
	for i := len(rev) - 1; i >= 0; i-- {
		s += string(rev[i])
	}
	return s
}

func (commaTicks) Ticks(min, max float64) []plot.Tick {
	tks := plot.DefaultTicks{}.Ticks(min, max)
	for i, t := range tks {
		if t.Label == "" {
			continue
		}
		tks[i].Label = addCommas(t.Label)
	}
	return tks
}

func readFromFile(filename string) ([]byte, error) {
	data, err := os.ReadFile(filename)
	if err != nil {
		fmt.Println("Error reading file:", err)
	}
	return data, err
}

func getMaxValue(values [][]float64) float64 {
	max := -1.0
	for _, row := range values {
		for _, val := range row {
			if val > max {
				max = val
			}
		}
	}
	return max
}

func Ploteo(values [][]float64, sort []string) {
	p := plot.New()
	p.Title.Text = "Comparing Methods of Sorting"
	p.X.Label.Text = "Size of Data"
	p.Y.Label.Text = "Delay Time"
	p.Y.Tick.Marker = commaTicks{}
	Xsort := []string{"0", "5", "10", "50", "100", "250", "500", "1500", "1000", "2500", "5000", "7500", "10000"}
	xticks := make([]plot.Tick, len(values[0]))
	for i := 0; i < len(values[0]); i++ {
		xticks[i] = plot.Tick{
			Value: float64(i),
			Label: Xsort[i],
		}
	}
	p.X.Tick.Marker = plot.ConstantTicks(xticks)
	maxY := getMaxValue(values)
	yTicks := []plot.Tick{}
	for i := 0.0; i <= maxY; {
		tickValue := i
		if maxY > 100 {
			yTicks = append(yTicks, plot.Tick{Value: tickValue, Label: strconv.FormatFloat(tickValue, 'f', 0, 64)})
			tickValue += 20.0
		} else if maxY > 50 {
			yTicks = append(yTicks, plot.Tick{Value: tickValue, Label: strconv.FormatFloat(tickValue, 'f', 1, 64)})
			tickValue += 10.0
		} else if maxY > 4 {
			yTicks = append(yTicks, plot.Tick{Value: tickValue, Label: strconv.FormatFloat(tickValue, 'f', 1, 64)})
			tickValue += 1.0
		} else if maxY > 1 {
			yTicks = append(yTicks, plot.Tick{Value: tickValue, Label: strconv.FormatFloat(tickValue, 'f', 1, 64)})
			tickValue += 0.1
		} else if maxY > 0.03 {
			yTicks = append(yTicks, plot.Tick{Value: tickValue, Label: strconv.FormatFloat(tickValue, 'f', 2, 64)})
			tickValue += 0.01
		} else if maxY > 0.02 {
			yTicks = append(yTicks, plot.Tick{Value: tickValue, Label: strconv.FormatFloat(tickValue, 'f', 3, 64)})
			tickValue += 0.005
		} else {
			yTicks = append(yTicks, plot.Tick{Value: tickValue, Label: strconv.FormatFloat(tickValue, 'f', 3, 64)})
			tickValue += 0.001
		}
		i = tickValue
	}
	p.Y.Min = 0.0
	p.Y.Max = float64(maxY)
	p.Y.Tick.Marker = plot.ConstantTicks(yTicks)
	lineStyles := []CustomLineStyle{
		{Width: vg.Points(1), Color: color.RGBA{R: 255, G: 0, B: 0, A: 255}},   // Rojo
		{Width: vg.Points(1), Color: color.RGBA{R: 0, G: 0, B: 255, A: 255}},   // Azul
		{Width: vg.Points(1), Color: color.RGBA{R: 0, G: 255, B: 0, A: 255}},   // Verde
		{Width: vg.Points(1), Color: color.RGBA{R: 128, G: 0, B: 128, A: 255}}, // Púrpura
		{Width: vg.Points(1), Color: color.RGBA{R: 255, G: 140, B: 0, A: 255}}, // Naranja
		{Width: vg.Points(1), Color: color.RGBA{R: 0, G: 128, B: 128, A: 255}}, // Verde Azulado
		{Width: vg.Points(1), Color: color.RGBA{R: 128, G: 128, B: 0, A: 255}}, // Amarillo-Oliva
		{Width: vg.Points(1), Color: color.RGBA{R: 128, G: 0, B: 0, A: 255}},   // Marrón
		{Width: vg.Points(1), Color: color.RGBA{R: 0, G: 0, B: 128, A: 255}},   // Azul Marino
		{Width: vg.Points(1), Color: color.RGBA{R: 0, G: 128, B: 0, A: 255}},   // Verde Oscuro
		{Width: vg.Points(1), Color: color.RGBA{R: 139, G: 0, B: 139, A: 255}}, // Violeta Oscuro
	}
	for i, vals := range values {
		pts := make(plotter.XYs, len(vals))
		for j, val := range vals {
			pts[j].X = float64(j)
			pts[j].Y = val
		}

		line, err := plotter.NewLine(pts)
		if err != nil {
			panic(err)
		}
		line.LineStyle = lineStyles[i].ConvertToLineStyle()
		p.Add(line)
		p.Legend.Add(sort[i], line)
	}
	p.Legend.Top = true
	p.Legend.Left = true
	if err := p.Save(5*vg.Inch, 6*vg.Inch, "Lineal.png"); err != nil {
		panic(err)
	}
	fmt.Println("Line chart saved as 'Lineal.png'")
}

func SplitLogLine(text string) []float64 {
	re := regexp.MustCompile(`\s+`)
	parts := re.Split(text, -1)
	var numbers []float64

	for _, part := range parts {
		part = strings.TrimSpace(part)
		if part != "" {
			number, err := strconv.ParseFloat(part, 64)
			if err != nil {
				fmt.Printf("Error parsing number '%s': %v\n", part, err)
			} else {
				numbers = append(numbers, number)
			}
		}
	}
	return numbers
}

func main() {
	sorts := []string{"Bubble", "Heap", "Insertion", "Selection", "Shell", "Merge", "Quick"}
	var values []string
	for i := 0; i < len(sorts); i++ {
		data, err := readFromFile(fmt.Sprintf("Lineal/%s", sorts[i]))
		if err != nil {
			fmt.Printf("Error al leer el archivo %s: %v\n", sorts[i], err)
			continue
		}
		values = append(values, string(data))
	}
	var valuesX [][]float64
	for i := 0; i < len(sorts); i++ {
		uwu := SplitLogLine(values[i])
		valuesX = append(valuesX, uwu)
	}
	Ploteo(valuesX, sorts)
}
