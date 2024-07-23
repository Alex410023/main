package file_system;

import javax.swing.JScrollPane;
import javax.swing.JPanel;
import javax.swing.JList;
import javax.swing.DefaultListModel;
import javax.swing.ListSelectionModel;

import java.util.ArrayList;

import java.io.File;

import lombok.Data;

@Data
public class FileCatalog extends JPanel {
    private ArrayList<File> fileList;
    private JList<String> fileNameList;
    private DefaultListModel<String> listModel;

    private ArrayList<File> fullFileList;
    private DefaultListModel<String> fullListModel;

    public FileCatalog() {
        fileList = new ArrayList<>();
        listModel = new DefaultListModel<>();
        fileNameList = new JList<>();
        fileNameList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

        fullFileList = new ArrayList<>();
        fullListModel = new DefaultListModel<>();
    }

    public void addToCatalog(File file, String name) {
        fileList.add(file);
        listModel.addElement(name);
        fileNameList.setModel(listModel);

        if (!fullFileList.contains(file)) {
            fullFileList.add(file);
            fullListModel.addElement(name);
        }
    }

    public boolean contains(File file) {
        return fileList.contains(file);
    }

    public void deleteFromCatalog(int fileIndex) {
        fileList.remove(fileList.get(fileIndex));
        listModel.removeElement(listModel.getElementAt(fileIndex));
        fileNameList.setModel(listModel);
    }

    public JScrollPane getFileListScrollPane() {
        JScrollPane scrollPane = new JScrollPane(fileNameList);
        scrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        return scrollPane;
    }
}