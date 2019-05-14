package;

import flixel.*;

class SteeringState extends FlxState {
    override public function create() {
        add(new Boid());

        super.create();
    }
}