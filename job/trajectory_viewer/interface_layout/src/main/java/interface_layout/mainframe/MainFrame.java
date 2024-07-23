package interface_layout.mainframe;

import interface_layout.mainframe.content.ContentPanel;
import interface_layout.mainframe.top.TopPanel;

import file_system.FileCatalog;

import java.awt.Rectangle;
import java.awt.BorderLayout;
import java.awt.GraphicsEnvironment;

import javax.swing.JFrame;

public class MainFrame extends JFrame {
    private TopPanel topPanel;
    private ContentPanel contentPanel;
    public MainFrame() {
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setExtendedState(JFrame.MAXIMIZED_BOTH);
        setTitle("Trajectory viewer");
        setLayout(new BorderLayout());

        Rectangle graphicsDevice = GraphicsEnvironment.getLocalGraphicsEnvironment().getMaximumWindowBounds();

        FileCatalog fileCatalog = new FileCatalog();

        contentPanel = new ContentPanel(fileCatalog, graphicsDevice.width, graphicsDevice.height);
        topPanel = new TopPanel(contentPanel, fileCatalog, graphicsDevice.width);

        add(topPanel, BorderLayout.NORTH);
        add(contentPanel, BorderLayout.CENTER);

        pack();
        setVisible(true);
    }
}