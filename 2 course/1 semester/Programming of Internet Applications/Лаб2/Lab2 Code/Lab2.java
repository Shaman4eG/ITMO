// Вариант 1959

public class Lab2 {
  public static void main(String[] args) {
    Remoraid mother = new Remoraid();
    Octillery daughter = new Octillery();
    Remoraid brother = new Octillery();

    mother.sniper();
    mother.defenseCurl(brother);
    daughter.conversion();
    daughter.focusEnergy();
    brother.moody();
    brother.focusEnergy();
    daughter.swordsDance();
    brother.sniper();
    daughter.defenseCurl(mother);
    mother.defenseCurl(daughter);
    daughter.defenseCurl(brother);
    daughter.sharpen();
    daughter.sniper();
    mother.workUp();
    mother.focusEnergy();
    ((Octillery)brother).batonPass();
  }
}

class Remoraid {
  byte jump;
  protected String psychic = "Psychic";
  double accuracy = 7.3;
  public int troublesome;
  protected String shadow = "Shadow";
  protected String psychicShadow = "PsychicShadow";
  protected static int inflatable = 99;

  public Remoraid() {
    jump = (byte) 0x99;
  }

  {
    jump = 57;
    troublesome = 060;
  }


  public void defenseCurl(Octillery p) {
    System.out.println("Remoraid attacks Octillery with Defense Curl");
  }

  public static void sniper() {
    System.out.println("Remoraid casts Sniper");
  }

  public void defenseCurl(Remoraid p) {
    System.out.println("Remoraid attacks Remoraid with Defense Curl");
  }

  public void focusEnergy() {
    System.out.println("Remoraid casts Focus Energy");
  }

  public void workUp() {
    double defense = 5.2;

    System.out.println((accuracy - defense) == 2.1);
  }

  public void sharpen() {
    System.out.println(inflatable + jump);
    System.out.println(troublesome - inflatable);
    System.out.println(jump - troublesome);
  }

  public void moody() {
    System.out.println(psychicShadow.equals("Psychic"+"Shadow"));
    System.out.println(psychicShadow.equals(psychic+shadow));
    System.out.println(psychicShadow == psychic+shadow);
    System.out.println(psychicShadow == "Psychic"+"Shadow");
    System.out.println(psychicShadow.equals(psychic+"Shadow"));
    System.out.println(psychicShadow == "Psychic"+shadow);
  }
}

class Octillery extends Remoraid {
  private int stealth;
  private String flyingShadow = "FlyingShadow";
  float depth = 5.3f;
  private String flying = "Flying";

  public Octillery() {
    stealth = 99;
  }


  public void focusEnergy() {
    System.out.println("Octillery casts Focus Energy");
  }

  public void conversion() {
    System.out.println(inflatable - stealth);
    System.out.println(stealth - jump);
    System.out.println(stealth + troublesome);
  }

  public void swordsDance() {
    float length = 6.2f;

    System.out.println((length - depth) == 0.9f);
  }

  public static void sniper() {
    System.out.println("Octillery casts Sniper");
  }

  public void batonPass() {
    System.out.println(flyingShadow == flying+shadow);
    System.out.println(flyingShadow == new String("Flying"+"Shadow"));
    System.out.println(flyingShadow == new String("FlyingShadow"));
    System.out.println(flyingShadow == (flying+shadow).intern());
  }

  public void defenseCurl(Octillery p) {
    System.out.println("Octillery attacks Octillery with Defense Curl");
  }

  public void defenseCurl(Remoraid p) {
    System.out.println("Octillery attacks Remoraid with Defense Curl");
  }
}


