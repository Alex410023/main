package file_system.buttons;

import file_system.FileChooser;

import javax.swing.JButton;
import javax.swing.JFileChooser;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class OpenButton extends JButton implements ActionListener {
    private FileChooser fileChooser;

    public OpenButton(FileChooser fileChooser) {
        super("Open a File");
        this.fileChooser = fileChooser;
        this.addActionListener(this);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        int returnVal = fileChooser.fileChooser.showOpenDialog(fileChooser);
        if (returnVal == JFileChooser.APPROVE_OPTION) {
            fileChooser.currentFile = fileChooser.fileChooser.getSelectedFile();
            try (BufferedReader br = new BufferedReader(new FileReader(fileChooser.currentFile))) {
                fileChooser.textArea.setText("");
                String line;
                while ((line = br.readLine()) != null) {
                    fileChooser.textArea.append(line + "\n");
                }
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        }
    }
}
