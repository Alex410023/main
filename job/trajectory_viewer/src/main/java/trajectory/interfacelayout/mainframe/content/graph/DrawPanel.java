package trajectory.interfacelayout.mainframe.content.graph;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

import trajectory.interfacelayout.mainframe.content.table.TablePanel;
import trajectory.interfacelayout.mainframe.content.table.Trajectory;

import javax.swing.BorderFactory;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.border.Border;

import java.awt.Color;
import java.awt.Dimension;
import java.util.ArrayList;

/**
 * A panel that displays trajectory data as a graph using the {@link JFreeChart} library.
 */
public class DrawPanel extends JPanel {
    TablePanel tablePanel;
    private final XYSeriesCollection dataset;
    private final XYLineAndShapeRenderer renderer;
    private final ArrayList<Trajectory> trajectories;

    /**
     * Constructs a new {@link DrawPanel} object with a white background and a gray border.
     *
     * @param tablePanel the table panel that contains the trajectory data
     */
    public DrawPanel(TablePanel tablePanel) {
        setBackground(Color.WHITE);
        Border borderLine = BorderFactory.createLineBorder(Color.GRAY);
        setBorder(borderLine);

        this.tablePanel = tablePanel;

        dataset = new XYSeriesCollection();
        renderer = new XYLineAndShapeRenderer();
        trajectories = new ArrayList<>();
    }

    /**
     * Adds a trajectory of the specified type to the graph and the trajectories list.
     *
     * @param type the type of trajectory to add
     */
    public void addTrajectory(TrajectoryType type) {
        if (tablePanel.getTableSize() <= 0) {
            JOptionPane.showMessageDialog(null, "Ошибка: поля таблицы пусты.");
            return;
        }

        ArrayList<Double> data;
        ArrayList<Double> time = tablePanel.getDataFromCol(0);
        Trajectory trajectory = new Trajectory();

        switch (type) {
            case X:
                data = tablePanel.getDataFromCol(1);
                trajectory.setCharacteristics(time, data, type, Color.RED);
                break;
            case Y:
                data = tablePanel.getDataFromCol(2);
                trajectory.setCharacteristics(time, data, type, Color.BLUE);
                break;
            case Z:
                data = tablePanel.getDataFromCol(3);
                trajectory.setCharacteristics(time, data, type, Color.GREEN);
                break;
            case VX:
                data = tablePanel.getDataFromCol(4);
                trajectory.setCharacteristics(time, data, type, Color.MAGENTA);
                break;
            case VY:
                data = tablePanel.getDataFromCol(5);
                trajectory.setCharacteristics(time, data, type, Color.ORANGE);
                break;
            case VZ:
                data = tablePanel.getDataFromCol(6);
                trajectory.setCharacteristics(time, data, type, Color.YELLOW);
                break;
        }

        trajectories.add(trajectory);
        drawTrajectory(trajectory);
    }

    /**
     * Draws a trajectory on the graph.
     *
     * @param trajectory the trajectory to draw
     */
    private void drawTrajectory(Trajectory trajectory) {
        XYSeries series = new XYSeries(trajectory.getType().toString());
        for (int i = 0; i < trajectory.getTime().size(); i++) {
            series.add(trajectory.getTime().get(i), trajectory.getData().get(i));
        }

        dataset.addSeries(series);
        renderer.setSeriesPaint(dataset.indexOf(trajectory.getType().toString()), trajectory.getColor());
        repaintChart();
    }

    /**
     * Deletes a trajectory of the specified type from the graph.
     *
     * @param type the type of trajectory to delete
     */
    public void deleteTrajectory(TrajectoryType type) {
        trajectories.removeIf(t -> t.getType() == type);
        displayTrajectories();
    }

    /**
     * Clears all trajectories of the specified group from the graph.
     *
     * @param group the group of trajectories to clear
     */
    public void clearGroup(TrajectoryGroup group) {
        trajectories.removeIf(t -> t.getType().getGroup() == group);
        displayTrajectories();
    }

    /**
     * Displays all trajectories stored in {@code trajectories} on the graph.
     */
    public void displayTrajectories() {
        dataset.removeAllSeries();

        for (Trajectory trajectory : trajectories) {
            XYSeries series = new XYSeries(trajectory.getType().toString());
            for (int i = 0; i < trajectory.getTime().size(); i++) {
                series.add(trajectory.getTime().get(i), trajectory.getData().get(i));
            }

            dataset.addSeries(series);
            renderer.setSeriesPaint(dataset.indexOf(series), trajectory.getColor());
        }

        repaintChart();
    }

    /**
     * Repaints the graph with the current dataset.
     */
    private void repaintChart() {
        JFreeChart chart = ChartFactory.createXYLineChart(
                "Графики",
                "Время (с)",
                "Значения",
                dataset,
                PlotOrientation.VERTICAL,
                false,
                false,
                false);

        chart.getXYPlot().setRenderer(renderer);

        ChartPanel chartPanel = new ChartPanel(chart);
        chartPanel.setPreferredSize(new Dimension(getWidth() - 20, getHeight() - 20));

        removeAll();
        add(chartPanel);
        revalidate();
        repaint();
    }

    /**
     * Updates the trajectories with the current data from the table panel.
     */
    public void updateTrajectories() {
        if (trajectories.isEmpty()) {
            return;
        }

        ArrayList<Double> time = tablePanel.getDataFromCol(0);
        for (Trajectory trajectory : trajectories) {
            int columnIndex = trajectory.getType().ordinal() + 1;
            ArrayList<Double> data = tablePanel.getDataFromCol(columnIndex);
            trajectory.setData(data);
            trajectory.setTime(time);
        }
        displayTrajectories();
    }

    /**
     * Clears the graph and removes all trajectories.
     */
    public void clearChart() {
        dataset.removeAllSeries();
        trajectories.clear();
        removeAll();
        revalidate();
        repaint();
    }
}