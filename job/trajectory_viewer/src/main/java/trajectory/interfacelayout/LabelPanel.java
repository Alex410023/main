package trajectory.interfacelayout;

import java.awt.FlowLayout;
import java.awt.Color;
import java.awt.Font;

import javax.swing.JLabel;
import javax.swing.JPanel;

/**
 * A panel that contains a single label with a specified text.
 */
public class LabelPanel extends JPanel {
    /**
     * Constructs a new {@link LabelPanel} object with the specified text.
     *
     * @param text the text to display on the label
     */
    public LabelPanel(String text) {
        setLayout(new FlowLayout(FlowLayout.CENTER));
        setBackground(Color.LIGHT_GRAY);

        JLabel label = new JLabel(text);
        label.setFont(new Font("Serif", Font.BOLD, 16));

        add(label);
    }
}
