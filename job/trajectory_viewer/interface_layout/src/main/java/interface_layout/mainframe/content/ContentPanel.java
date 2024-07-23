package interface_layout.mainframe.content;

import interface_layout.mainframe.content.catalog.CatalogPanel;
import interface_layout.mainframe.content.file.FilePanel;
import interface_layout.mainframe.content.graph.GraphPanel;
import interface_layout.mainframe.content.table.TablePanel;

import file_system.FileCatalog;

import java.awt.BorderLayout;
import java.awt.Dimension;
import javax.swing.JPanel;
import javax.swing.JSplitPane;

public class ContentPanel extends JPanel {
    private CatalogPanel catalogPanel;
    private FilePanel filePanel;
    private TablePanel tablePanel;
    private GraphPanel graphPanel;
    public ContentPanel(FileCatalog fileCatalog, int initWidth, int initHeight) {
        setLayout(new BorderLayout());
        setPreferredSize(new Dimension(initWidth, initHeight - 40));

        filePanel = new FilePanel(initWidth / 7 * 2, (initHeight - 40) / 7 * 4);
        tablePanel = new TablePanel(initWidth / 7 * 5, (initHeight - 40) / 7 * 3);
        catalogPanel = new CatalogPanel(filePanel, tablePanel, fileCatalog, initWidth / 7 * 2, (initHeight - 40) / 7 * 3);
        graphPanel = new GraphPanel(initWidth / 7 * 5, (initHeight - 40) / 7 * 4);

        JSplitPane topSplitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, catalogPanel, tablePanel);
        JSplitPane bottomSplitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, filePanel, graphPanel);
        JSplitPane midSplitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT, topSplitPane, bottomSplitPane);

        topSplitPane.setDividerLocation(initWidth / 7 * 2);
        bottomSplitPane.setDividerLocation(initWidth / 7 * 2);
        midSplitPane.setDividerLocation((initHeight - 40) / 7 * 3);

        add(midSplitPane, BorderLayout.CENTER);
    }

    public FilePanel getFilePanel() {
        return filePanel;
    }
    public TablePanel getTablePanel() {
        return tablePanel;
    }
}