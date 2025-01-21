package trajectory.interfacelayout.mainframe.content.catalog;

import lombok.Getter;
import trajectory.interfacelayout.ErrorLogger;
import trajectory.interfacelayout.mainframe.content.ContentPanel;
import trajectory.interfacelayout.mainframe.content.file.FileCatalog;
import trajectory.interfacelayout.LabelPanel;
import trajectory.interfacelayout.mainframe.content.file.FilePanel;
import trajectory.interfacelayout.mainframe.content.graph.GraphPanel;
import trajectory.interfacelayout.mainframe.content.table.TablePanel;

import java.awt.BorderLayout;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

/**
 * A panel that displays a list of files and allows the user to select and close files.
 * The panel also handles saving edited files and displaying the selected file's data in the table and graph panels.
 */
public class CatalogPanel extends JPanel {
    private final LabelPanel labelPanel;
    /**
     * -- GETTER --
     *  Returns the file catalog.
     *  */
    @Getter
    private FileCatalog fileCatalog;
    /**
     * -- GETTER --
     *  Returns the currently selected file.
     */
    @Getter
    private File selectedFile;
    private int selectedIndex;
    private boolean isFileEdited = false;
    private FilePanel filePanel;
    private TablePanel tablePanel;
    private GraphPanel graphPanel;

    /**
     A flag to indicate whether the selection change is being made by the user
     (used not to trigger {@link ListSelectionListener} when changing selected catalog item)
     */
    private boolean isSelectionChangeByUser = false;

    /**
     * Constructs a new {@link CatalogPanel} object with a label panel.
     */
    public CatalogPanel() {
        setLayout(new BorderLayout());
        labelPanel = new LabelPanel("Каталог");
    }

    /**
     * Initializes the catalog panel with the specified content panel and file catalog.
     *
     * @param contentPanel the content panel that contains the file, table, and graph panels
     * @param fileCatalog the file catalog that contains the list of files
     */
    public void initCatalogPanel(ContentPanel contentPanel, FileCatalog fileCatalog) {
        this.fileCatalog = fileCatalog;
        this.filePanel = contentPanel.getFilePanel();
        this.tablePanel = contentPanel.getTablePanel();
        this.graphPanel = contentPanel.getGraphPanel();

        fileCatalog.getFileNameList().addListSelectionListener(new ListSelectionListener() {
            @Override
            public void valueChanged(ListSelectionEvent e) {
                if (!e.getValueIsAdjusting() && !isSelectionChangeByUser) {
                    selectedIndex = fileCatalog.getFileNameList().getSelectedIndex();

                    if (selectedIndex >= 0) { // if an item got selected
                        if (isFileEdited) {
                            int editedFileHandled = handleEditedFile(selectedFile);
                            if (editedFileHandled == JOptionPane.YES_OPTION) {
                                displaySelectedFile();
                            } else if (editedFileHandled == JOptionPane.NO_OPTION) {
                                displaySelectedFile();
                            } else {
                                setSelectedFile(selectedFile);
                            }

                        } else {
                            displaySelectedFile();
                        }
                    } else { // if an item got deselected
                        if (isFileEdited) {
                            if (handleEditedFile(selectedFile) != JOptionPane.CANCEL_OPTION) {
                                clearPanels();
                            } else {
                                setSelectedFile(selectedFile);
                            }
                        } else {
                            clearPanels();
                        }
                    }
                }
            }
        });

        CatalogContextMenu popupMenu = new CatalogContextMenu(this);
        fileCatalog.getFileNameList().addMouseListener(popupMenu);

        JScrollPane scrollPane = fileCatalog.getFileListScrollPane();

        add(labelPanel, BorderLayout.NORTH);
        add(scrollPane, BorderLayout.CENTER);
    }

    /**
     * Displays the selected file's data in the table and graph panels.
     */
    private void displaySelectedFile() {
        selectedFile = fileCatalog.getFileList().get(selectedIndex);
        tablePanel.writeFileOnTable(selectedFile);
        filePanel.writeOnPanel(tablePanel.getTableStringData());
    }

    /**
     * Clears the file, table, and graph panels.
     */
    private void clearPanels() {
        filePanel.writeOnPanel("");
        tablePanel.clean();
        selectedFile = null;
        graphPanel.clearGraphPanel();
    }

    /**
     * Sets the selected file to the specified file.
     *
     * @param file the file to be selected
     */
    public void setSelectedFile(File file) {
        isSelectionChangeByUser = true;
        int index = fileCatalog.getFileList().indexOf(file);
        if (index >= 0) {
            fileCatalog.getFileNameList().setSelectedIndex(index);
            selectedIndex = index;
            selectedFile = file;
        }
        isSelectionChangeByUser = false;
    }

    /**
     * Returns true if the selected file has been edited, false otherwise.
     *
     * @return true if the selected file has been edited, false otherwise
     */
    public boolean getFileWasEdited() {
        return isFileEdited;
    }

    /**
     * Sets the edited flag for the selected file to the specified value.
     *
     * @param isEdited true if the selected file has been edited, false otherwise
     */
    public void setFileEdited(boolean isEdited) {
        if (isEdited) {
            if (!isFileEdited) {
                String fileName = fileCatalog.getListModel().get(selectedIndex);
                fileCatalog.getListModel().set(selectedIndex, fileName + "*");
                isFileEdited = true;
            }
        } else if (isFileEdited) {
            int index = fileCatalog.getFileList().indexOf(selectedFile);
            String fileName = fileCatalog.getListModel().get(index);
            fileCatalog.getListModel().set(index, fileName.substring(0, fileName.length() - 1));
            isFileEdited = false;
        }
    }

    /**
     * Closes the selected file and handles any unsaved changes.
     */
    public void closeSelectedFile() {
        if (selectedFile != null) {
            if (isFileEdited) {
                if (handleEditedFile(selectedFile) != JOptionPane.CANCEL_OPTION) {
                    clearPanels();
                    fileCatalog.deleteFromCatalog(selectedIndex);
                    JOptionPane.showMessageDialog(null, "Файл закрыт.");
                } else {
                    setSelectedFile(selectedFile);
                }
            } else {
                clearPanels();
                fileCatalog.deleteFromCatalog(selectedIndex);
                JOptionPane.showMessageDialog(null, "Файл закрыт.");
            }
        }

        renameFilesInCatalog();
    }

    /**
     * Handles an edited file by prompting the user to save changes, discard changes, or cancel the operation.
     *
     * @param file the edited file
     * @return the user's choice ({@code JOptionPane.YES_OPTION}, {@code JOptionPane.NO_OPTION}, or {@code JOptionPane.CANCEL_OPTION})
     */
    public int handleEditedFile(File file) {
        int option = JOptionPane.showOptionDialog(null,
                "Присутствуют несохраненные изменения. Хотите сохранить их?",
                "Несохраненные изменения",
                JOptionPane.YES_NO_CANCEL_OPTION,
                JOptionPane.QUESTION_MESSAGE,
                null,
                new String[]{"Да", "Нет", "Отмена"},
                "Да");

        if (option == JOptionPane.YES_OPTION && !saveEditedFile(file)) {
            option = JOptionPane.CANCEL_OPTION;
        } else if (option == JOptionPane.NO_OPTION) {
            revertChanges();
        }

        return option;
    }

    /**
     * Reverts any changes made to the selected file.
     */
    private void revertChanges() {
        tablePanel.writeFileOnTable(selectedFile);
        filePanel.writeOnPanel(tablePanel.getTableStringData());
        setFileEdited(false);
    }

    /**
     * Prompts to save the specified file.
     *
     * @param file the file to save to
     * @return true if the file was saved successfully, false otherwise
     */
    public boolean saveEditedFile(File file) {
        int option = JOptionPane.showOptionDialog(
                null,
                "Файл был изменён. Что вы хотите сделать?",
                "Несохранённые изменения",
                JOptionPane.YES_NO_CANCEL_OPTION,
                JOptionPane.QUESTION_MESSAGE,
                null,
                new String[]{"Сохранить", "Сохранить как", "Отмена"},
                "Сохранить");

        if (option == JOptionPane.YES_OPTION) {
            saveToFile(file, file.getName());
            setFileEdited(false);
            return true;
        } else if (option == JOptionPane.NO_OPTION) {
            JFileChooser fileChooser = new JFileChooser();
            fileChooser.setDialogTitle("Сохранить файл как");
            fileChooser.setApproveButtonText("Сохранить");

            int userSelection = fileChooser.showSaveDialog(this);

            if (userSelection == JFileChooser.APPROVE_OPTION) {
                File fileToSave = fileChooser.getSelectedFile();
                saveToFile(fileToSave, fileToSave.getName());
            }

            tablePanel.writeFileOnTable(selectedFile);
            filePanel.writeOnPanel(tablePanel.getTableStringData());
            setFileEdited(false);
            return true;
        }
        return false;
    }

    /**
     * Saves the file with the specified file name.
     *
     * @param fileToSave the file to be saved
     * @param fileName the name of the file
     */
    public void saveToFile(File fileToSave, String fileName) {
        if (fileToSave != null) {
            try (FileWriter fileWriter = new FileWriter(fileToSave)) {
                fileWriter.write(tablePanel.getTableStringData());
                setFileEdited(false);
                JOptionPane.showMessageDialog(null, "Файл успешно сохранён: " + fileName);
            } catch (IOException ex) {
                String errorMessage = "Ошибка при сохранении файла: " + ex.getMessage();
                ErrorLogger.logError(errorMessage);
                JOptionPane.showMessageDialog(
                        null,
                        errorMessage,
                        "Ошибка",
                        JOptionPane.ERROR_MESSAGE);
            }
        }
    }

    /**
     * Renames files in the catalog that match the pattern "Траектория N", adjusting N to the actual file number.
     */
    private void renameFilesInCatalog () {
        String regex = "^Траектория \\d+$";

        for (int i = 0; i < fileCatalog.getFileList().size(); i++) {
            String displayedName = fileCatalog.getListModel().get(i);

            if (displayedName.matches(regex)) {
                String renamedName = displayedName.replaceAll(regex, "Траектория " + (i + 1));

                fileCatalog.getListModel().set(i, renamedName);
            }
        }
    }
}