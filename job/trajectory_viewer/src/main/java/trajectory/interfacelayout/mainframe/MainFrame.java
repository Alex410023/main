package trajectory.interfacelayout.mainframe;

import trajectory.interfacelayout.mainframe.content.file.FileCatalog;
import trajectory.interfacelayout.mainframe.content.ContentPanel;
import trajectory.interfacelayout.mainframe.top.TopPanel;

import java.awt.Rectangle;
import java.awt.BorderLayout;
import java.awt.GraphicsEnvironment;

import javax.swing.JFrame;

/**
 * The main frame of the application that contains the top panel and the content panel.
 */
public class MainFrame extends JFrame {
    /**
     * Constructs a new {@link MainFrame} object.
     */
    public MainFrame() {
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setExtendedState(JFrame.MAXIMIZED_BOTH);
        setTitle("Trajectory viewer");
        setLayout(new BorderLayout());

        Rectangle graphicsDevice = GraphicsEnvironment.getLocalGraphicsEnvironment().getMaximumWindowBounds();

        FileCatalog fileCatalog = new FileCatalog();

        ContentPanel contentPanel = new ContentPanel(fileCatalog, graphicsDevice.width, graphicsDevice.height);
        TopPanel topPanel = new TopPanel(contentPanel, fileCatalog);

        add(topPanel, BorderLayout.NORTH);
        add(contentPanel, BorderLayout.CENTER);

        pack();
        setVisible(true);
    }
}