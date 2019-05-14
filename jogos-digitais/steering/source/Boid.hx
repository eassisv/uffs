package;

import flixel.*;
import flixel.math.FlxVector;

class Boid extends FlxSprite {
    public function new () {
        super(FlxG.width / 2, FlxG.height / 2);
        
        velocity.x = 10;
        velocity.y = 10;
    }

    override public function update(e:Float):Void {
        super.update(e);
        var steering = new FlxVector(0, 0);
        // steering.addPoint(flee(FlxG.mouse.x, FlxG.mouse.y));
        steering.addPoint(seek(FlxG.mouse.x, FlxG.mouse.y));
        steering.addPoint(arrive(FlxG.mouse.x, FlxG.mouse.y, 50));
        // arrive(FlxG.mouse.x, FlxG.mouse.y, 50);
        acceleration.x = steering.x;
        acceleration.y = steering.y;
    }

    public function seek(x_:Int, y_:Int):FlxVector {
        var target = new FlxVector(x_, y_);
        var seek = target.subtractPoint(
            new FlxVector(x, y)
        );
        seek.normalize().scale(20);
        return seek;
    }

    public function flee(x_:Int, y_:Int):FlxVector {
        return seek(x_, y_).scale(-1);
    }

    public function arrive(x_:Int, y_:Int, radius:Float):FlxVector {
        var target = new FlxVector(x_, y_);
        var direct = target.subtractPoint(
            new FlxVector(x, y)
        );
        if (direct.length <= radius) {
            return new FlxVector(velocity.x, velocity.y)
                .normalize().scale(-20);
        }
        return new FlxVector();
    }
}