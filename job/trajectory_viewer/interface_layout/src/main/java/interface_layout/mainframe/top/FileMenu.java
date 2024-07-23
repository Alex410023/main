package interface_layout.mainframe.top;

import interface_layout.mainframe.content.ContentPanel;
import interface_layout.mainframe.top.fileoptions.OpenMenuItem;
import interface_layout.mainframe.top.fileoptions.OpenRecentMenuItem;
import interface_layout.mainframe.top.fileoptions.CloseMenuItem;
import interface_layout.mainframe.top.fileoptions.CloseAllMenuItems;

import file_system.FileCatalog;

import javax.swing.JMenu;


public class FileMenu extends JMenu {
    public FileMenu(ContentPanel contentPanel, FileCatalog fileCatalog, String menuText) {
        super(menuText);

        add(new OpenMenuItem(contentPanel, fileCatalog));
        add(new OpenRecentMenuItem(contentPanel, fileCatalog));
        add(new CloseMenuItem(contentPanel, fileCatalog));
        add(new CloseAllMenuItems(contentPanel, fileCatalog));

    }
}
