package trajectory.interfacelayout.mainframe.content.table;

import java.awt.Color;
import java.util.ArrayList;

import lombok.Data;
import trajectory.interfacelayout.mainframe.content.graph.TrajectoryType;

/**
 * A class that represents a trajectory with its type, data, time, and color.
 */
@Data
public class Trajectory {
    private TrajectoryType type;
    private ArrayList<Double> data;
    private ArrayList<Double> time;
    private Color color;

    /**
     * Sets the characteristics of the trajectory.
     *
     * @param time the time data for the trajectory
     * @param data the data for the trajectory
     * @param type the type of the trajectory
     * @param color the color to use when displaying the trajectory
     */
    public void setCharacteristics(ArrayList<Double> time, ArrayList<Double> data,
                                   TrajectoryType type, Color color) {
        this.data = data;
        this.time = time;
        this.type = type;
        this.color = color;
    }
}
