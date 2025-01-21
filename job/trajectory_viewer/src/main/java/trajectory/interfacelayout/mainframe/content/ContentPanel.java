package trajectory.interfacelayout.mainframe.content;

import lombok.Getter;
import trajectory.interfacelayout.mainframe.content.file.FileCatalog;
import trajectory.interfacelayout.mainframe.content.catalog.CatalogPanel;
import trajectory.interfacelayout.mainframe.content.file.FilePanel;
import trajectory.interfacelayout.mainframe.content.graph.GraphPanel;
import trajectory.interfacelayout.mainframe.content.table.TablePanel;

import java.awt.BorderLayout;
import javax.swing.JPanel;
import javax.swing.JSplitPane;

/**
 * A panel that contains the main content of the application, including the catalog panel, file panel, table panel, and graph panel.
 */
@Getter
public class ContentPanel extends JPanel {
    private final CatalogPanel catalogPanel;
    private final FilePanel filePanel;
    private TablePanel tablePanel;
    private final GraphPanel graphPanel;

    /**
     * Constructs a new {@link ContentPanel} object with the specified file catalog and initial width and height.
     *
     * @param fileCatalog the file catalog to use for the catalog panel
     * @param initWidth the initial width of the content panel
     * @param initHeight the initial height of the content panel
     */
    public ContentPanel(FileCatalog fileCatalog, int initWidth, int initHeight) {
        setLayout(new BorderLayout());

        filePanel = new FilePanel();
        catalogPanel = new CatalogPanel();
        tablePanel = new TablePanel();
        tablePanel = new TablePanel();
        graphPanel = new GraphPanel(tablePanel);
        tablePanel.initTablePanel(this);
        catalogPanel.initCatalogPanel(this, fileCatalog);


        JSplitPane topSplitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, catalogPanel, tablePanel);
        JSplitPane bottomSplitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, filePanel, graphPanel);
        JSplitPane midSplitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT, topSplitPane, bottomSplitPane);

        topSplitPane.setDividerLocation(initWidth / 7 * 2);
        bottomSplitPane.setDividerLocation(initWidth / 7 * 2);
        midSplitPane.setDividerLocation((initHeight - 40) / 7 * 3);

        add(midSplitPane, BorderLayout.CENTER);
    }
}