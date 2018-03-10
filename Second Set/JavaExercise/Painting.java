

public final class Painting extends Masterpiece
{
	private final int length;
	private final int width;
	private final int surface;
	private final pTechnique technique;

	public Painting(final String creator_,final int year_,final mMovement movement_,final mCondition condition_,
					final int length_,final int width_,final pTechnique technique_)
	{
		super(creator_,year_,movement_,condition_);
		length = length_;
		width = width_;
		surface = width_ * length_;
		technique = technique_;

		System.out.println("Creating an instance of Painting\n");
	}

	public void getInfo(){
		System.out.println("Painting Info");
		super.getInfo();

		System.out.println("Length: " + length);
		System.out.println("Width: " + width);
		System.out.println("Surface: " + surface);

		System.out.println("Technique: " + technique.toString().substring(0,1).toUpperCase() + technique.toString().substring(1).toLowerCase());

		return;
	}

	public boolean evaluate(final mMovement movement_,final mCondition condition_)
	{
		return ((super.getMovement().equals(movement_)) && ((super.getCondition().equals(condition_)) || (super.getCondition().equals(mCondition.EXCELLENT) && condition_ .equals(mCondition.GOOD))));	
	}

	public boolean evaluate(final mMovement movement){

		return this.evaluate(movement,mCondition.GOOD);
	}
}