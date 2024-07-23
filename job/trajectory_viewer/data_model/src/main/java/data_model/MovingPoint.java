package data_model;

public class MovingPoint {
    private double time;
    private Point point;
    private double velocityX;
    private double velocityY;
    private double velocityZ;

    public MovingPoint() {
    }

    public MovingPoint(double time, Point point, double velocityX, double velocityY, double velocityZ) {
        this.time = time;
        this.point = point;
        this.velocityX = velocityX;
        this.velocityY = velocityY;
        this.velocityZ = velocityZ;
    }

    public double getTime() {
        return time;
    }

    public void setTime(double time) {
        this.time = time;
    }

    public Point getPoint() {
        return point;
    }

    public void setPoint(Point point) {
        this.point = point;
    }

    public double getVelocityX() {
        return velocityX;
    }

    public void setVelocityX(double velocityX) {
        this.velocityX = velocityX;
    }

    public double getVelocityY() {
        return velocityY;
    }

    public void setVelocityY(double velocityY) {
        this.velocityY = velocityY;
    }

    public double getVelocityZ() {
        return velocityZ;
    }

    public void setVelocityZ(double velocityZ) {
        this.velocityZ = velocityZ;
    }
}
