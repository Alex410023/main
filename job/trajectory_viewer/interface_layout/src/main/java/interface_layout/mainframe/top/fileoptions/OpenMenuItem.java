package interface_layout.mainframe.top.fileoptions;

import interface_layout.mainframe.content.ContentPanel;
import interface_layout.mainframe.content.file.FilePanel;
import file_system.FileCatalog;

import javax.swing.JMenuItem;
import javax.swing.JFileChooser;
import javax.swing.filechooser.FileNameExtensionFilter;
import javax.swing.JOptionPane;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


public class OpenMenuItem extends JMenuItem implements ActionListener {
    private JFileChooser fileChooser;
    private FileCatalog fileCatalog;
    private FilePanel filePanel;
    private int index = 0;

    public OpenMenuItem(ContentPanel contentPanel, FileCatalog fileCatalog) {
        super("Открыть");
        addActionListener(this);

        this.fileCatalog = fileCatalog;
        this.filePanel = contentPanel.getFilePanel();
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        fileChooser = new JFileChooser();
        FileNameExtensionFilter filter = new FileNameExtensionFilter("Text Files", "txt");
        fileChooser.setFileFilter(filter);

        int returnVal = fileChooser.showOpenDialog(fileChooser);
        if (returnVal == JFileChooser.APPROVE_OPTION) {
            if (!fileCatalog.contains(fileChooser.getSelectedFile())) {
                String name = getUserInput();
                fileCatalog.addToCatalog(fileChooser.getSelectedFile(), name);;
                index++;
            } else if (filePanel.isEdited()) {
                filePanel.handleEditedFile(fileChooser.getSelectedFile());
            } else {
                JOptionPane.showMessageDialog(null, "Файл уже открыт");
            }
        }
    }

    private String getUserInput() {
        String defaultName = "Траектория " + index;
        String name = JOptionPane.showInputDialog(null, "Введите имя",
                "Имя траектории", JOptionPane.QUESTION_MESSAGE, null, null, defaultName).toString();
       return name != null ? name : defaultName;
    }
}
