require("class")

ScriptComponent = class()

rotationSpeed = 0.1

moveAccel = 2


function ScriptComponent:Update(this)

	--Rotate player with mouse
	angle = Merlin.InputManager.GetAxis("Xaxis") * rotationSpeed
	this:GetTransform():RotateAboutY(angle)

	--Move player with keyboard, simple true/false
	moveLeftKey = Merlin.InputManager.GetKey("MoveLeft");
	moveRightKey = Merlin.InputManager.GetKey("MoveRight");
	moveFwdKey = Merlin.InputManager.GetKey("MoveFwd");
	moveBwdKey = Merlin.InputManager.GetKey("MoveBwd");
	moveJumpKey = Merlin.InputManager.GetKey("MoveJump");

	--Get shoot Key
	shootBallKey = Merlin.InputManager.GetKey("ShootBall");


	--Default to no movement
	moveSide = 0; moveFwd = 0;

	--If Key Pressed set to 1 or -1 depending on direction
	if (moveLeftKey) {	moveSide = 1	}
	if (moveRightKey) {	moveSide = -1	}
	if (moveFwdKey) {	moveFwd  = 1	}
	if (moveBwdKey) {	moveFwd  = -1	}

	--Pass move data to character controller
	this:GetPlayerController():ControlCharacter(moveSide, moveFwd, moveJumpKey)

	--Pass shoot data onto character controller
	this:GetPlayerController():ShootBall()

end


function ScriptComponent:OnCollisionEnter(this, collider)
	print("Lua Collider Enter ".. collider:GetName())
end


function ScriptComponent:OnCollisionExit(this, collider)
	print("Lua Collider Exit ".. collider:GetName())
end
