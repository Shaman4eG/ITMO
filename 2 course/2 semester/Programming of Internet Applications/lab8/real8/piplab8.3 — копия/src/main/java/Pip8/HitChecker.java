package Pip8;

public class HitChecker {

    private static final int MULTIPLIER_OF_R = 25;

    public boolean CheckHit(int x, int y, int r)
    {
        r *= MULTIPLIER_OF_R;

        if (hit(x, y, r)) return true;
        else return false;
    }

    // Square -> triangle -> arc
    private boolean hit(int x, int y, int r)
    {
        return
                (
                        x >= -r &&
                        x <= 0  &&
                        y >= 0  &&
                        y <= r
                ) ||
                (
                        y >= -x - r &&
                        y <= 0      &&
                        x <= 0
                ) ||
                (
                        x * x + y * y <= (r / 2) * (r / 2) &&
                        x >= 0                             &&
                        y <= 0
                );
    }
}
