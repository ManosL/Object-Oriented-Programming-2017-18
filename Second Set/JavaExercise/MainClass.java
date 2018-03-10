import java.util.Random; 

public class MainClass{
	public static final int CURRENT_YEAR = 2018;

	public static final int MIN_LENGTH = 150;
	public static final int MAX_LENGTH = 300;

	public static final int MIN_WIDTH = 150;
	public static final int MAX_WIDTH = 300;

	public static final int MIN_VOLUME = 150;
	public static final int MAX_VOLUME = 300;

	public static void main(String[] args){
		final int argc = args.length;

		Artifact[] artifacts;
		int artifact_number;
		mMovement auction_movement = null;		//Initializing the following variables
		mCondition auction_condition = null;

		Random rand = new Random(System.currentTimeMillis());   //Seed the random number generator

		//Checking if the user gave right arguments

		if(argc != 3){
			System.out.println("Wrong input");
			System.out.println("Right format of input");
			System.out.println("<number of artifacts> <movement value> <condition value>");

			return;
		}

		if(Integer.parseInt(args[0]) <= 0){
			System.out.println("Wrong input");
			System.out.println("Number of artifacts should take a number bigger than 0.");

			return;
		}
		else{
			artifact_number = Integer.parseInt(args[0]);		//Converting integer to string
		}

		if(!(args[1].equals("impressionism")) && !(args[1].equals("expressionism")) && !(args[1].equals("naturalism"))){
			System.out.println("Wrong input");
			System.out.println("Movement should take these values: impressionism,expressionism or naturalism.");
			return ;
		}
		else{
			if(args[1].equals("impressionism")) auction_movement = mMovement.IMPRESSIONISM;
				else
					if(args[1].equals("expressionism")) auction_movement = mMovement.EXPRESSIONISM;
				else
					if(args[1].equals("naturalism")) auction_movement = mMovement.NATURALISM;
		}

		if(!(args[2].equals("bad")) && !(args[2].equals("good")) && !(args[2].equals("excellent"))){
			System.out.println("Wrong input");
			System.out.println("Condition should take these values: bad,good or excellent.");
			return;
		}
		else{
			if(args[2].equals("bad")) auction_condition = mCondition.BAD;
				else
					if(args[2].equals("good")) auction_condition = mCondition.GOOD;
				else
					if(args[2].equals("excellent")) auction_condition = mCondition.EXCELLENT;
		}		

		artifacts = new Artifact[artifact_number];

		for(int i = 0;i < artifact_number;i++){
			String current = Integer.toString(i + 1);
			mMovement move = intToMoveEnum(rand.nextInt(3));
			mCondition cond = intToCondEnum(rand.nextInt(3));

			if(rand.nextInt(2) == 0){
				pTechnique tech = intToTechEnum(rand.nextInt(3));
				artifacts[i] = new Painting("Creator"+current,rand.nextInt(CURRENT_YEAR),move,cond,(rand.nextInt((MAX_LENGTH - MIN_LENGTH)))+ MIN_LENGTH,(rand.nextInt((MAX_WIDTH - MIN_WIDTH)))+MIN_WIDTH,tech);
			}
			else{
				sMaterial material = intToMaterialEnum(rand.nextInt(3));
				artifacts[i] = new Sculpture("Creator"+current,rand.nextInt(CURRENT_YEAR),move,cond,rand.nextInt(MAX_VOLUME-MIN_VOLUME)+MIN_VOLUME,material);
			}
		}

		auction(artifacts,auction_movement,auction_condition);		
	}

	public static void auction(final Artifact[] artifacts,final mMovement movement,final mCondition condition){

		final int length = artifacts.length;

			for(int i = 0;i < length;i++){
				artifacts[i].getIndex();
				artifacts[i].getInfo();
				System.out.println("Evaluate returned: " + artifacts[i].evaluate(movement,condition) + "\n");
			}

			return;
	}

	//I wrote this function because I didn't found a ready
	//way to convert Integer to Enum
	
	public static mMovement intToMoveEnum(final int num){

		switch(num){
			case 0:
				return mMovement.IMPRESSIONISM;
			case 1:
				return mMovement.EXPRESSIONISM;
			case 2:
				return mMovement.NATURALISM;	
		}

		return null;
	}

	public static mCondition intToCondEnum(final int num){

		switch(num){
			case 0:
				return mCondition.BAD;
			case 1:
				return mCondition.GOOD;
			case 2:
				return mCondition.EXCELLENT;
		}

		return null;
	}

	public static pTechnique intToTechEnum(final int num){

		switch(num){
			case 0:
				return pTechnique.OIL;
			case 1:
				return pTechnique.AQUARELLE;
			case 2:
				return pTechnique.TEMPERA;
		}

		return null;
	}

	public static sMaterial intToMaterialEnum(final int num){

		switch(num){
			case 0:
				return sMaterial.IRON;
			case 1:
				return sMaterial.STONE;
			case 2:
				return sMaterial.WOOD;
		}

		return null;
	}
}