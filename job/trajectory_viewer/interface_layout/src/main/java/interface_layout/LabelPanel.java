package interface_layout;

import java.awt.FlowLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;

import javax.swing.JLabel;
import javax.swing.JPanel;

public class LabelPanel extends JPanel {
    public LabelPanel(String text) {
        setLayout(new FlowLayout(FlowLayout.CENTER));
        setBackground(Color.LIGHT_GRAY);
        setPreferredSize(new Dimension(getWidth(), 30));

        JLabel label = new JLabel(text);
        label.setFont(new Font("Serif", Font.BOLD, 16));

        add(label);
    }
}
