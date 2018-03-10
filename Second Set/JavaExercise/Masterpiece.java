
public abstract class Masterpiece extends Artifact     
{									   
	private final mMovement movement;
	private mCondition condition;

	public Masterpiece(final String creator_,final int year_,final mMovement movement_,final mCondition condition_)
	{
		super(creator_,year_);			//Calling the constructor of Artifact
		movement = movement_;
		condition = condition_;

		System.out.println("Creating an instance of Masterpiece");
	}

	public void getInfo(){
		super.getInfo();

		//Making the print to have the first word capitalized
		
		System.out.println("Movement: " + movement.toString().substring(0,1).toUpperCase() + movement.toString().substring(1).toLowerCase());

		System.out.println("Condition: " + condition.toString().substring(0,1).toUpperCase() + condition.toString().substring(1).toLowerCase());			
	}

	public final mMovement getMovement(){ return movement; }

	public final mCondition getCondition(){ return condition; }


}