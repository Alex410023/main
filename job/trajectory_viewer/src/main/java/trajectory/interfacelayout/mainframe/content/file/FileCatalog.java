package trajectory.interfacelayout.mainframe.content.file;

import javax.swing.JScrollPane;
import javax.swing.JList;
import javax.swing.DefaultListModel;
import javax.swing.ListSelectionModel;

import java.util.ArrayList;

import java.io.File;

import lombok.Data;

/**
 * A class that represents a catalog of files.
 * The catalog contains a list of files and a {@link JList} that displays the file names.
 */
@Data
public class FileCatalog {
    private ArrayList<File> fileList;
    private JList<String> fileNameList;
    private DefaultListModel<String> listModel;

    /**
     * Constructs a new {@link FileCatalog} object with an empty file list and a {@link JList} with single selection mode.
     */
    public FileCatalog() {
        fileList = new ArrayList<>();
        listModel = new DefaultListModel<>();
        fileNameList = new JList<>();
        fileNameList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
    }

    /**
     * Adds a file to the catalog with the specified name.
     *
     * @param file the file to add
     * @param name the name to display for the file in the {@link JList}
     */
    public void addToCatalog(File file, String name) {
        fileList.add(file);
        listModel.addElement(name);
        fileNameList.setModel(listModel);
    }

    /**
     * Returns true if the catalog contains the specified file, false otherwise.
     *
     * @param file the file to check for
     * @return true if the catalog contains the specified file, false otherwise
     */
    public boolean contains(File file) {
        return fileList.contains(file);
    }

    /**
     * Deletes the file at the specified index from the catalog.
     *
     * @param fileIndex the index of the file to be deleted
     */
    public void deleteFromCatalog(int fileIndex) {
        fileList.remove(fileList.get(fileIndex));
        listModel.removeElement(listModel.getElementAt(fileIndex));
        fileNameList.setModel(listModel);
    }

    /**
     * Returns a {@link JScrollPane} that contains the {@link JList} of file names.
     *
     * @return a {@link JScrollPane} that contains the {@link JList} of file names
     */
    public JScrollPane getFileListScrollPane() {
        JScrollPane scrollPane = new JScrollPane(fileNameList);
        scrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        return scrollPane;
    }
}