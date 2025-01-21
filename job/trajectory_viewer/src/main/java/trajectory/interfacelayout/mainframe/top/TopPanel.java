package trajectory.interfacelayout.mainframe.top;

import trajectory.interfacelayout.mainframe.content.file.FileCatalog;
import trajectory.interfacelayout.mainframe.content.ContentPanel;
import trajectory.interfacelayout.mainframe.top.fileoptions.OpenMenuItem;
import trajectory.interfacelayout.mainframe.top.fileoptions.SaveMenuItem;
import trajectory.interfacelayout.mainframe.top.fileoptions.SaveAsMenuItem;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;

import javax.swing.JMenuBar;
import javax.swing.JPanel;
import javax.swing.JMenu;

/**
 * A panel that contains the menu bar at the top of the application.
 */
public class TopPanel extends JPanel {
    /**
     * Constructs a new {@link TopPanel} object with the specified content panel and file catalog.
     *
     * @param contentPanel the content panel that contains the catalog panel, table panel, and file panel
     * @param fileCatalog the file catalog to use for adding and saving trajectory files
     */
    public TopPanel(ContentPanel contentPanel, FileCatalog fileCatalog) {
        setBackground(new Color(106, 153, 208));

        setLayout(new FlowLayout(FlowLayout.LEFT));

        JMenuBar menuBar = new JMenuBar();

        JMenu fileMenu = new JMenu("Файл");
        fileMenu.add(new OpenMenuItem(contentPanel, fileCatalog));
        fileMenu.add(new SaveMenuItem(contentPanel));
        fileMenu.add(new SaveAsMenuItem(contentPanel));

        menuBar.add(fileMenu);
        menuBar.setPreferredSize(new Dimension(52, 30));
        add(menuBar);
    }
}