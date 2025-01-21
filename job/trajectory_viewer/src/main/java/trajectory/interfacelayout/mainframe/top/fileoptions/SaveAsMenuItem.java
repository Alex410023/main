package trajectory.interfacelayout.mainframe.top.fileoptions;

import trajectory.interfacelayout.mainframe.content.ContentPanel;
import trajectory.interfacelayout.mainframe.content.catalog.CatalogPanel;

import javax.swing.JFileChooser;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

/**
 * A menu item that allows the user to save the currently selected trajectory file to a new location.
 */
public class SaveAsMenuItem extends JMenuItem implements ActionListener {
    private final CatalogPanel catalogPanel;

    /**
     * Constructs a new {@link SaveAsMenuItem} object with the specified content panel.
     *
     * @param contentPanel the content panel that contains the catalog panel
     */
    public SaveAsMenuItem(ContentPanel contentPanel) {
        super("Сохранить как");
        addActionListener(this);

        this.catalogPanel = contentPanel.getCatalogPanel();
    }

    /**
     * Handles the action event when the menu item is selected.
     *
     * @param e the action event that triggered the method call
     */
    @Override
    public void actionPerformed(ActionEvent e) {
        File selectedFile = catalogPanel.getSelectedFile();
        if (selectedFile != null) {
            JFileChooser fileChooser = new JFileChooser();
            fileChooser.setDialogTitle("Сохранить файл");
            fileChooser.setApproveButtonText("Сохранить");

            int userSelection = fileChooser.showSaveDialog(this);

            if (userSelection == JFileChooser.APPROVE_OPTION) {
                File fileToSave = fileChooser.getSelectedFile();
                catalogPanel.saveToFile(fileToSave, fileToSave.getName());

                int index = catalogPanel.getFileCatalog().getFileList().indexOf(selectedFile);
                catalogPanel.getFileCatalog().getFileList().set(index, fileToSave);
                catalogPanel.setSelectedFile(fileToSave);
            }
        } else {
            JOptionPane.showMessageDialog(
                    null,
                    "Файл не выбран",
                    "Ошибка",
                    JOptionPane.ERROR_MESSAGE);
        }
    }
}