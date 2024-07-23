package file_system.buttons;

import file_system.FileChooser;

import javax.swing.JButton;
import javax.swing.JOptionPane;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

import java.io.File;

class RenameButton extends JButton implements ActionListener {
    private FileChooser fileChooser;

    public RenameButton(FileChooser fileChooser) {
        super("Rename a File");
        this.fileChooser = fileChooser;
        this.addActionListener(this);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (fileChooser.currentFile != null) {
            String newName = JOptionPane.showInputDialog(fileChooser, "Enter the new file name:");
            if (newName != null && !newName.isEmpty()) {
                File newFile = new File(fileChooser.currentFile.getParent(), newName);
                if (fileChooser.currentFile.renameTo(newFile)) {
                    JOptionPane.showMessageDialog(fileChooser, "File renamed successfully.");
                    fileChooser.currentFile = newFile;
                } else {
                    JOptionPane.showMessageDialog(fileChooser, "Failed to rename the file.");
                }
            }
        } else {
            JOptionPane.showMessageDialog(fileChooser, "No file is currently open.");
        }
    }

}