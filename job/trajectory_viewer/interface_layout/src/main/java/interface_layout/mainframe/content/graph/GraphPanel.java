package interface_layout.mainframe.content.graph;

import interface_layout.LabelPanel;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;

import javax.swing.JPanel;
import javax.swing.JScrollPane;

public class GraphPanel extends JPanel {
    private LabelPanel graphLabel;
    private VisualPanel visualPanel;
    public GraphPanel(int initWidth, int initHeight) {
        setLayout(new BorderLayout());
        setPreferredSize(new Dimension(initWidth, initHeight));

        graphLabel = new LabelPanel("График");

        visualPanel = new VisualPanel();
        visualPanel.setPreferredSize(new Dimension(initWidth, initHeight - 100));

        JScrollPane scrollPane = new JScrollPane(visualPanel);
        scrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);

        add(graphLabel, BorderLayout.NORTH);
        add(scrollPane, BorderLayout.CENTER);
    }

}