package file_system.buttons;

import file_system.FileChooser;

import javax.swing.JButton;
import javax.swing.JFileChooser;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

class SaveButton extends JButton implements ActionListener {
    private FileChooser fileChooser;

    public SaveButton(FileChooser fileChooser) {
        super("Save a File");
        this.fileChooser = fileChooser;
        this.addActionListener(this);
    }

    public void actionPerformed(ActionEvent e) {
        int returnVal = fileChooser.fileChooser.showSaveDialog(fileChooser);
        if (returnVal == JFileChooser.APPROVE_OPTION) {
            fileChooser.currentFile = fileChooser.fileChooser.getSelectedFile();
            try (BufferedWriter bw = new BufferedWriter(new FileWriter(fileChooser.currentFile))) {
                bw.write(fileChooser.textArea.getText());
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        }
    }
}
