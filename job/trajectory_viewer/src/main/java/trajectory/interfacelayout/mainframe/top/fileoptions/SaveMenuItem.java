package trajectory.interfacelayout.mainframe.top.fileoptions;

import trajectory.interfacelayout.mainframe.content.catalog.CatalogPanel;
import trajectory.interfacelayout.mainframe.content.file.FileCatalog;
import trajectory.interfacelayout.mainframe.content.ContentPanel;

import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

/**
 * A menu item that allows the user to save the currently selected trajectory file to its original location.
 */
public class SaveMenuItem extends JMenuItem implements ActionListener {
    private final CatalogPanel catalogPanel;

    /**
     * Constructs a new {@link SaveMenuItem} object with the specified content panel.
     *
     * @param contentPanel the content panel that contains the catalog panel
     */
    public SaveMenuItem(ContentPanel contentPanel) {
        super("Сохранить");
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
            catalogPanel.saveToFile(selectedFile, selectedFile.getName());
        } else {
            JOptionPane.showMessageDialog(
                    null,
                    "Файл не выбран",
                    "Ошибка",
                    JOptionPane.ERROR_MESSAGE);
        }
    }
}
