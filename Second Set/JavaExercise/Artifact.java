package Main;

public abstract class Artifact
{
	private final int Index;
	private final String creator;
	private final int year;

	public static int curr_index = 1;

	public Artifact(final String creator_,final int year_){  //Initializing the fields

		creator = creator_;
		year = year_;
		Index = curr_index;

		curr_index++;

		System.out.println("Creating an instance of Artifact");
	}

	public void getInfo(){
		System.out.println("Creator: " + creator);
		System.out.println("Creation year: " + year);
	}

	public abstract boolean evaluate(final mMovement movement,final mCondition condition);
	public abstract boolean evaluate(final mMovement movement);

	public final void getIndex(){ 
		System.out.println("Artifact's Index: " + Index);
	}

}