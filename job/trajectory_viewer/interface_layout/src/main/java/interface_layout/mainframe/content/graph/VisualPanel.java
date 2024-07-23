package interface_layout.mainframe.content.graph;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;

import javax.swing.JPanel;

public class VisualPanel extends JPanel {
    public VisualPanel() {
        setLayout(new BorderLayout());
//        setPreferredSize(new Dimension(getWidth(), 100));
        setBackground(Color.WHITE);

        CharacteristicsPanel characteristicsPanel = new CharacteristicsPanel();
        DrawPanel drawPanel = new DrawPanel();
        GraphOptionsPanel graphOptionsPanel = new GraphOptionsPanel();

        add(characteristicsPanel, BorderLayout.NORTH);
        add(drawPanel, BorderLayout.CENTER);
        add(graphOptionsPanel, BorderLayout.SOUTH);
    }
}