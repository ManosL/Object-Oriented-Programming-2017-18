
public final class Sculpture extends Masterpiece
{
	private final int volume;
	private final sMaterial material;

	public Sculpture(final String creator_,final int year_,final mMovement movement_,final mCondition condition_,
					 final int volume_,final sMaterial material_)
	{
		super(creator_,year_,movement_,condition_);
		volume = volume_;
		material = material_;

		System.out.println("Creating an instance of Sculpture\n");
	}

	public void getInfo(){
		System.out.println("Sculpture Info");
		super.getInfo();

		System.out.println("Volume: " + volume);

		System.out.println("Material: " + material.toString().substring(0,1).toUpperCase() + material.toString().substring(1).toLowerCase());
	}

	public boolean evaluate(final mMovement movement_,final mCondition condition_)
	{
		return ((super.getMovement().equals(movement_)) && (super.getCondition().equals(condition_)));
	}

	public boolean evaluate(final mMovement movement){

		return this.evaluate(movement,mCondition.EXCELLENT);
	}		
}