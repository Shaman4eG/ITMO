package Pip8;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class PointsKeeper {

    private ArrayList<Point> points;

    public PointsKeeper()
    {
        points = new ArrayList<Point>();
    }

    public void AddPoint(Point point)
    {
        points.add(point);
    }

    public List<Point> GetPoints()
    {
        return Collections.unmodifiableList(points);
    }
}
