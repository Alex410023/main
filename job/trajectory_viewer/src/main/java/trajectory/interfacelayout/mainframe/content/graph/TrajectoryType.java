package trajectory.interfacelayout.mainframe.content.graph;

import lombok.Getter;

/**
 * An enumeration of the trajectory types.
 */
@Getter
public enum TrajectoryType {
    X(TrajectoryGroup.COORDINATES),
    Y(TrajectoryGroup.COORDINATES),
    Z(TrajectoryGroup.COORDINATES),
    VX(TrajectoryGroup.SPEED),
    VY(TrajectoryGroup.SPEED),
    VZ(TrajectoryGroup.SPEED);

    private final TrajectoryGroup group;

    TrajectoryType(TrajectoryGroup group) {
        this.group = group;
    }

}