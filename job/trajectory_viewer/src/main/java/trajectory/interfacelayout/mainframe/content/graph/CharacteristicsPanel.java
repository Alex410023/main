package trajectory.interfacelayout.mainframe.content.graph;

import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.Box;
import javax.swing.JPanel;

import java.awt.FlowLayout;
import java.awt.Dimension;
import java.awt.event.ItemListener;
import java.awt.event.ItemEvent;
import java.util.ArrayList;

import lombok.Data;
/**
 * A panel that displays checkboxes for selecting the trajectory characteristics to display on a graph.
 */
@Data
public class CharacteristicsPanel extends JPanel {
    private BaseCheckBox xCheckBox;
    private BaseCheckBox yCheckBox;
    private BaseCheckBox zCheckBox;
    private BaseCheckBox xVCheckBox;
    private BaseCheckBox yVCheckBox;
    private BaseCheckBox zVCheckBox;
    private ArrayList<BaseCheckBox> checkBoxes;

    private DrawPanel drawPanel;
    private GraphPanel graphPanel;


    /**
     * Constructs a new {@link CharacteristicsPanel} object with checkboxes for selecting the trajectory characteristics to display on a graph.
     *
     * @param graphPanel the graph panel that contains the draw panel
     */
    public CharacteristicsPanel(GraphPanel graphPanel) {
        setLayout(new FlowLayout(FlowLayout.LEFT));

        this.graphPanel = graphPanel;
        this.drawPanel = graphPanel.getDrawPanel();

        checkBoxes = new ArrayList<>();

        add(new JLabel("Координаты:"));

        xCheckBox = new BaseCheckBox("X, м", TrajectoryType.X);
        checkBoxes.add(xCheckBox);

        yCheckBox = new BaseCheckBox("Y, м", TrajectoryType.Y);
        checkBoxes.add(yCheckBox);

        zCheckBox = new BaseCheckBox("Z, м", TrajectoryType.Z);
        checkBoxes.add(zCheckBox);

        xVCheckBox = new BaseCheckBox("Vx, м/с", TrajectoryType.VX);
        checkBoxes.add(xVCheckBox);

        yVCheckBox = new BaseCheckBox("Vy, м/с", TrajectoryType.VY);
        checkBoxes.add(yVCheckBox);

        zVCheckBox = new BaseCheckBox("Vz, м/с", TrajectoryType.VZ);
        checkBoxes.add(zVCheckBox);

        for (BaseCheckBox checkBox : checkBoxes) {
            add(checkBox);
            if (checkBox.equals(zCheckBox)) {
                add(Box.createRigidArea(new Dimension(100, 0)));
                add(new JLabel("Проекции скорости:"));
            }
        }

    }

    /**
     * Deselects all checkboxes in the panel.
     */
    public void deselectAllCheckboxes() {
        for (BaseCheckBox checkBox : checkBoxes) {
            checkBox.setSelected(false);
        }
    }

    /**
     * A custom {@link JCheckBox} that listens for item state changes and updates the graph panel accordingly.
     */
    private class BaseCheckBox extends JCheckBox implements ItemListener {
        private final TrajectoryType checkBoxType;

        /**
         * Constructs a new {@link BaseCheckBox} object with the specified text and trajectory type.
         *
         * @param text the text to display on the checkbox
         * @param checkBoxType the trajectory type associated with the checkbox
         */
        public BaseCheckBox(String text, TrajectoryType checkBoxType) {
            super(text);
            this.checkBoxType = checkBoxType;
            addItemListener(this);
        }

        /**
         * Handles item state changes and updates the graph panel accordingly.
         *
         * @param e the item event that triggered the method call
         */
        @Override
        public void itemStateChanged(ItemEvent e) {
            BaseCheckBox checkBox = (BaseCheckBox) e.getSource();

            if (e.getStateChange() == ItemEvent.SELECTED) {
                drawPanel.addTrajectory(checkBoxType);
            } else if (e.getStateChange() == ItemEvent.DESELECTED) {
                drawPanel.deleteTrajectory(checkBoxType);
            }

            if (checkBox.isSelected()) {
                if (checkBox == xCheckBox || checkBox == yCheckBox || checkBox == zCheckBox) {
                    xVCheckBox.setSelected(false);
                    yVCheckBox.setSelected(false);
                    zVCheckBox.setSelected(false);
                    drawPanel.clearGroup(TrajectoryGroup.SPEED);
                } else {
                    xCheckBox.setSelected(false);
                    yCheckBox.setSelected(false);
                    zCheckBox.setSelected(false);
                    drawPanel.clearGroup(TrajectoryGroup.COORDINATES);
                }
            }

            boolean allDeselected = true;
            for (BaseCheckBox cb : checkBoxes) {
                if (cb.isSelected()) {
                    allDeselected = false;
                    break;
                }
            }

            if (allDeselected) {
                graphPanel.clearGraphPanel();
            }
        }
    }
}


