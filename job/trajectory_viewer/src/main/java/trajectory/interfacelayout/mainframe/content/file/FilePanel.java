package trajectory.interfacelayout.mainframe.content.file;

import trajectory.interfacelayout.LabelPanel;

import java.awt.BorderLayout;

import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.JScrollPane;

/**
 * A panel that displays the contents of a file in a {@link JTextArea}.
 */
public class FilePanel extends JPanel {
    private final JTextArea textArea;

    /**
     * Constructs a new {@link FilePanel} object with a label panel and a non-editable {@link JTextArea} wrapped in a {@link JScrollPane}.
     */
    public FilePanel() {
        setLayout(new BorderLayout());

        LabelPanel fileLabel = new LabelPanel("Файл");

        textArea = new JTextArea(20, 30);
        textArea.setEditable(false);

        JScrollPane scrollPane = new JScrollPane(textArea);

        add(fileLabel, BorderLayout.NORTH);
        add(scrollPane, BorderLayout.CENTER);
    }

    /**
     * Writes the specified text to the {@link JTextArea} in the panel.
     *
     * @param text the text to be written on the {@link JTextArea}
     */
    public void writeOnPanel(String text) {
        textArea.setText(text);
    }
}
