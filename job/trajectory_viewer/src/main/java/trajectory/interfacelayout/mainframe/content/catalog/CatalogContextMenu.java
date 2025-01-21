package trajectory.interfacelayout.mainframe.content.catalog;

import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

/**
 * A mouse adapter that displays a context menu when the user right-clicks on a file in the catalog panel.
 */
public class CatalogContextMenu extends MouseAdapter {
    private final CatalogPanel catalogPanel;

    /**
     * Constructs a new {@link CatalogContextMenu} object with the specified {@link CatalogPanel}.
     *
     * @param catalogPanel the {@link CatalogPanel} that contains the file catalog
     */
    public CatalogContextMenu(CatalogPanel catalogPanel) {
        this.catalogPanel = catalogPanel;
    }

    /**
     * Shows the context menu when the user presses the mouse button.
     *
     * @param e the {@link MouseEvent} that triggered the method call
     */
    @Override
    public void mousePressed(MouseEvent e) {
        if (e.isPopupTrigger()) {
            showPopupMenu(e);
        }
    }

    /**
     * Shows the context menu when the user releases the mouse button.
     *
     * @param e the {@link MouseEvent} that triggered the method call
     */
    @Override
    public void mouseReleased(MouseEvent e) {
        if (e.isPopupTrigger()) {
            showPopupMenu(e);
        }
    }

    /**
     * Shows the context menu at the specified location.
     *
     * @param e the {@link MouseEvent} that triggered the method call
     */
    private void showPopupMenu(MouseEvent e) {
        int index = catalogPanel.getFileCatalog().getFileNameList().locationToIndex(e.getPoint());
        catalogPanel.getFileCatalog().getFileNameList().setSelectedIndex(index);
        JPopupMenu popupMenu = createPopupMenu();
        popupMenu.show(e.getComponent(), e.getX(), e.getY());
    }

    /**
     * Creates the context menu with a "Close" option.
     *
     * @return the {@link JPopupMenu} object that represents the context menu
     */
    private JPopupMenu createPopupMenu() {
        JPopupMenu popupMenu = new JPopupMenu();
        JMenuItem closeMenuItem = new JMenuItem("Закрыть");
        closeMenuItem.addActionListener(e -> catalogPanel.closeSelectedFile());
        popupMenu.add(closeMenuItem);
        return popupMenu;
    }
}