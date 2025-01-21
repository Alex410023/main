package trajectory.interfacelayout.mainframe.top.fileoptions;

import trajectory.interfacelayout.ErrorLogger;
import trajectory.interfacelayout.mainframe.content.catalog.CatalogPanel;
import trajectory.interfacelayout.mainframe.content.file.FileCatalog;
import trajectory.interfacelayout.mainframe.content.ContentPanel;
import trajectory.interfacelayout.mainframe.content.file.FilePanel;
import trajectory.interfacelayout.mainframe.content.table.TablePanel;

import javax.swing.JMenuItem;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

/**
 * A menu item that allows the user to open a trajectory file and add it to the catalog panel.
 */
public class OpenMenuItem extends JMenuItem implements ActionListener {
    private final FileCatalog fileCatalog;
    private final CatalogPanel catalogPanel;
    private final TablePanel tablePanel;
    private final FilePanel filePanel;

    /**
     * Constructs a new {@link OpenMenuItem} object with the specified content panel and file catalog.
     *
     * @param contentPanel the content panel that contains the catalog panel, table panel, and file panel
     * @param fileCatalog the file catalog to use for adding trajectory files
     */
    public OpenMenuItem(ContentPanel contentPanel, FileCatalog fileCatalog) {
        super("Открыть");
        addActionListener(this);

        this.fileCatalog = fileCatalog;
        this.catalogPanel = contentPanel.getCatalogPanel();
        this.tablePanel = contentPanel.getTablePanel();
        this.filePanel = contentPanel.getFilePanel();
    }

    /**
     * Handles the action event when the menu item is selected.
     *
     * @param e the action event that triggered the method call
     */
    @Override
    public void actionPerformed(ActionEvent e) {
        JFileChooser fileChooser = new JFileChooser();

        if (tablePanel.getTable().isEditing()) {
            tablePanel.getTable().getCellEditor().stopCellEditing();
        }

        int returnVal = fileChooser.showOpenDialog(fileChooser);
        if (returnVal == JFileChooser.APPROVE_OPTION) {
            File selectedFile = fileChooser.getSelectedFile();

            if (!selectedFile.getName().endsWith(".txt")) {
                ErrorLogger.logError("Ошибка при открытии файла: " + selectedFile.getName() + " не является txt файлом");
                JOptionPane.showMessageDialog(null, "Ошибка при открытии файла: " + selectedFile.getName() + " не является txt файлом");
                return;
            }

            if (fileCatalog.contains(selectedFile)) {
                JOptionPane.showMessageDialog(null, "Файл уже открыт");
            }

            if (!catalogPanel.getFileWasEdited() && !fileCatalog.contains(selectedFile)) {
                String name = getUserInput();
                fileCatalog.addToCatalog(selectedFile, name);
            } else if (catalogPanel.getFileWasEdited()) {
                int editedFileHandled = catalogPanel.handleEditedFile(selectedFile);
                if (editedFileHandled != JOptionPane.CANCEL_OPTION) {
                    tablePanel.writeFileOnTable(selectedFile);
                    filePanel.writeOnPanel(tablePanel.getTableStringData());

                    String name = getUserInput();
                    fileCatalog.addToCatalog(selectedFile, name);
                }
            }
        }
    }

    /**
     * Prompts the user to enter a name for the trajectory file.
     *
     * @return the name entered by the user, or a default name if the user cancels the input dialog
     */
    private String getUserInput() {
        int index = fileCatalog.getFileList().size() + 1;

        String defaultName = "Траектория " + index;
        String name = JOptionPane.showInputDialog(null, "Введите имя",
                "Имя траектории", JOptionPane.QUESTION_MESSAGE, null, null, defaultName).toString();
        return name != null && !name.trim().isEmpty() ? name : defaultName;
    }
}