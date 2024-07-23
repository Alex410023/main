package file_system;

import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.JFileChooser;
import javax.swing.filechooser.FileNameExtensionFilter;

import java.io.File;

public class FileChooser extends JPanel {
    public JTextArea textArea;
    public JFileChooser fileChooser;
    public File currentFile;

    public FileChooser() {
        fileChooser = new JFileChooser();

        // Set the file filter for the file chooser
        FileNameExtensionFilter filter = new FileNameExtensionFilter("Text Files", "txt");
        fileChooser.setFileFilter(filter);

        JPanel buttonPanel = new JPanel();

        this.add(buttonPanel, "North");
    }
}