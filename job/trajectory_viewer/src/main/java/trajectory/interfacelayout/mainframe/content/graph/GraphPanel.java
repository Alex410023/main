package trajectory.interfacelayout.mainframe.content.graph;

import lombok.Getter;
import trajectory.interfacelayout.LabelPanel;
import trajectory.interfacelayout.mainframe.content.table.TablePanel;

import java.awt.BorderLayout;

import javax.swing.JPanel;
import javax.swing.JScrollPane;

/**
 * A panel that displays trajectory data as a graph with checkboxes for selecting the trajectory characteristics to display.
 */
public class GraphPanel extends JPanel {
    @Getter
    private final DrawPanel drawPanel;
    private final CharacteristicsPanel characteristicsPanel;

    /**
     * Constructs a new {@link GraphPanel} object with a label panel, a draw panel, and a characteristics panel.
     *
     * @param tablePanel the table panel that contains the trajectory data
     */
    public GraphPanel(TablePanel tablePanel) {
        setLayout(new BorderLayout());

        LabelPanel graphLabel = new LabelPanel("График");

        drawPanel = new DrawPanel(tablePanel);
        characteristicsPanel = new CharacteristicsPanel(this);

        JPanel visualPanel = new JPanel(new BorderLayout());
        visualPanel.add(characteristicsPanel, BorderLayout.NORTH);
        visualPanel.add(drawPanel, BorderLayout.CENTER);

        JScrollPane scrollPane = new JScrollPane(visualPanel);
        scrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);

        add(graphLabel, BorderLayout.NORTH);
        add(scrollPane, BorderLayout.CENTER);
    }

    /**
     * Clears the graph panel by deselecting all checkboxes and clearing the chart.
     */
    public void clearGraphPanel() {
        characteristicsPanel.deselectAllCheckboxes();
        drawPanel.clearChart();
    }
}