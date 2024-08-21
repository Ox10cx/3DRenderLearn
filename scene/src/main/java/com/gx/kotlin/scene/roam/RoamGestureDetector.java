package com.gx.kotlin.scene.roam;

import android.content.Context;
import android.graphics.PointF;
import android.util.Log;
import android.view.MotionEvent;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import com.gx.kotlin.scene.gesture.AndroidGesturesManager;
import com.gx.kotlin.scene.gesture.MoveGestureDetector;
import com.gx.kotlin.scene.gesture.RotateGestureDetector;
import com.gx.kotlin.scene.gesture.ShoveGestureDetector;
import com.gx.kotlin.scene.gesture.StandardScaleGestureDetector;

import java.util.HashSet;
import java.util.Set;

public final class RoamGestureDetector {
    private final Transform mTransform;

    private AndroidGesturesManager mGesturesManager;

    RoamGestureDetector(@Nullable Context context, Transform transform) {
        this.mTransform = transform;

        if (context != null) {
            // Initialize gestures manager
            AndroidGesturesManager androidGesturesManager = new AndroidGesturesManager(context);

            initializeGesturesManager(androidGesturesManager, true);

            // Initialize gesture listeners
            initializeGestureListeners(context, true);
        }
    }

    private void initializeGesturesManager(@NonNull AndroidGesturesManager androidGesturesManager,
                                           boolean setDefaultMutuallyExclusives) {
        if (setDefaultMutuallyExclusives) {
            Set<Integer> shoveScaleSet = new HashSet<>();
            shoveScaleSet.add(AndroidGesturesManager.GESTURE_TYPE_SHOVE);
            shoveScaleSet.add(AndroidGesturesManager.GESTURE_TYPE_SCALE);

            Set<Integer> shoveRotateSet = new HashSet<>();
            shoveRotateSet.add(AndroidGesturesManager.GESTURE_TYPE_SHOVE);
            shoveRotateSet.add(AndroidGesturesManager.GESTURE_TYPE_ROTATE);

            Set<Integer> ScaleLongPressSet = new HashSet<>();
            ScaleLongPressSet.add(AndroidGesturesManager.GESTURE_TYPE_SCALE);
            ScaleLongPressSet.add(AndroidGesturesManager.GESTURE_TYPE_LONG_PRESS);

            androidGesturesManager.setMutuallyExclusiveGestures(shoveScaleSet, shoveRotateSet, ScaleLongPressSet);
        }

        mGesturesManager = androidGesturesManager;
//        mGesturesManager.getRotateGestureDetector().setAngleThreshold(3f);
    }

    private void initializeGestureListeners(@NonNull Context context, boolean attachDefaultListeners) {
        if (attachDefaultListeners) {
            MoveGestureListener moveGestureListener = new MoveGestureListener();
            RotateGestureListener rotateGestureListener = new RotateGestureListener();
            ShoveGestureListener shoveGestureListener = new ShoveGestureListener();
            ScaleGestureListener scaleGestureListener = new ScaleGestureListener();


            mGesturesManager.setMoveGestureListener(moveGestureListener);
            mGesturesManager.setRotateGestureListener(rotateGestureListener);
            mGesturesManager.setShoveGestureListener(shoveGestureListener);
            mGesturesManager.setStandardScaleGestureListener(scaleGestureListener);

//            StandardGestureListener standardGestureListener = new StandardGestureListener(
//                    context.getResources().getDimension(
//                            com.mapbox.android.gestures.R.dimen.mapbox_defaultScaleSpanSinceStartThreshold));
//            ScaleGestureListener scaleGestureListener = new ScaleGestureListener(
//                    context.getResources().getDimension(R.dimen.mapbox_density_constant),
//                    context.getResources().getDimension(R.dimen.mapbox_minimum_scale_speed),
//                    context.getResources().getDimension(R.dimen.mapbox_minimum_angled_scale_speed),
//                    context.getResources().getDimension(R.dimen.mapbox_minimum_scale_velocity)
//            );
//            RotateGestureListener rotateGestureListener = new RotateGestureListener(
//                    context.getResources().getDimension(R.dimen.mapbox_minimum_scale_span_when_rotating),
//                    context.getResources().getDimension(R.dimen.mapbox_density_constant),
//                    context.getResources().getDimension(R.dimen.mapbox_angular_velocity_multiplier),
//                    context.getResources().getDimension(R.dimen.mapbox_minimum_angular_velocity),
//                    context.getResources().getDimension(
//                            com.mapbox.android.gestures.R.dimen.mapbox_defaultScaleSpanSinceStartThreshold));
//            ShoveGestureListener shoveGestureListener = new ShoveGestureListener();
//            TapGestureListener tapGestureListener = new TapGestureListener();

//            gesturesManager.setStandardGestureListener(standardGestureListener);
//            gesturesManager.setMoveGestureListener(moveGestureListener);
//            gesturesManager.setStandardScaleGestureListener(scaleGestureListener);
//            gesturesManager.setRotateGestureListener(rotateGestureListener);
//            gesturesManager.setShoveGestureListener(shoveGestureListener);
//            gesturesManager.setMultiFingerTapGestureListener(tapGestureListener);
        }
    }


    boolean onTouchEvent(@Nullable MotionEvent motionEvent) {
        // Framework can return null motion events in edge cases #9432
        if (motionEvent == null) {
            return false;
        }

        // Check and ignore non touch or left clicks
        if ((motionEvent.getButtonState() != 0) && (motionEvent.getButtonState() != MotionEvent.BUTTON_PRIMARY)) {
            return false;
        }

        boolean result = mGesturesManager.onTouchEvent(motionEvent);

        return result;
    }

    @NonNull
    private PointF getRotateFocalPoint(@NonNull RotateGestureDetector detector) {
        return detector.getFocalPoint();
    }

    private PointF getScaleFocalPoint(@NonNull StandardScaleGestureDetector detector) {
        return detector.getFocalPoint();
    }

    private final class MoveGestureListener extends MoveGestureDetector.SimpleOnMoveGestureListener {

        @Override
        public boolean onMove(@NonNull MoveGestureDetector detector, float distanceX, float distanceY) {
            if (distanceX != 0 || distanceY != 0) {
                // Scroll the map
                mTransform.moveBy(-distanceX, -distanceY, 0 /*no duration*/);
            }
            return true;
        }
    }

    private final class RotateGestureListener extends RotateGestureDetector.SimpleOnRotateGestureListener {
        @Override
        public boolean onRotate(@NonNull RotateGestureDetector detector, float rotationDegreesSinceLast, float rotationDegreesSinceFirst) {
            PointF focalPoint = getRotateFocalPoint(detector);
            mTransform.setBearing(rotationDegreesSinceLast, focalPoint.x, focalPoint.y);
            return true;
        }
    }

    private final class ShoveGestureListener extends ShoveGestureDetector.SimpleOnShoveGestureListener {
        @Override
        public boolean onShoveBegin(@NonNull ShoveGestureDetector detector) {
            mGesturesManager.getMoveGestureDetector().setEnabled(false);
            return true;
        }

        @Override
        public boolean onShove(@NonNull ShoveGestureDetector detector, float deltaPixelsSinceLast, float deltaPixelsSinceStart) {
            double pitch = 0.1f * deltaPixelsSinceLast;
            mTransform.setPitch(pitch);
            return true;
        }

        @Override
        public void onShoveEnd(@NonNull ShoveGestureDetector detector, float velocityX, float velocityY) {
            mGesturesManager.getMoveGestureDetector().setEnabled(false);
        }
    }

    private final class ScaleGestureListener extends StandardScaleGestureDetector.SimpleStandardOnScaleGestureListener {
        private final float minimumGestureSpeed;
        private final float minimumAngledGestureSpeed;

        public ScaleGestureListener() {
            minimumGestureSpeed = 0.6f;
            minimumAngledGestureSpeed = 0.9f;
        }

        @Override
        public boolean onScaleBegin(@NonNull StandardScaleGestureDetector detector) {
            if (detector.getPreviousSpan() > 0) {
                float currSpan = detector.getCurrentSpan();
                float prevSpan = detector.getPreviousSpan();
                double currTime = detector.getCurrentEvent().getEventTime();
                double prevTime = detector.getPreviousEvent().getEventTime();
                if (currTime == prevTime) {
                    return false;
                }
                double speed = Math.abs(currSpan - prevSpan) / (currTime - prevTime);
                if (speed < minimumGestureSpeed) {
                    // do not scale if the minimal gesture speed is not met
                    return false;
                } else if (!mGesturesManager.getRotateGestureDetector().isInProgress()) {
                    float rotationDeltaSinceLast = mGesturesManager.getRotateGestureDetector().getDeltaSinceLast();
                    if (Math.abs(rotationDeltaSinceLast) > 0.4 && speed < minimumAngledGestureSpeed) {
                        // do not scale in case we're preferring to start rotation
                        return false;
                    }

                    mGesturesManager.getRotateGestureDetector().setEnabled(false);

                }
            } else {
                return false;
            }

            return true;
        }

        @Override
        public boolean onScale(@NonNull StandardScaleGestureDetector detector) {
            PointF focalPoint = getScaleFocalPoint(detector);
            double zoomBy =
                    (Math.log(detector.getScaleFactor()) / Math.log(Math.PI / 2)) * 0.65f;
            mTransform.zoomBy(zoomBy, focalPoint);
            return true;
        }

        @Override
        public void onScaleEnd(@NonNull StandardScaleGestureDetector detector, float velocityX, float velocityY) {
            mGesturesManager.getRotateGestureDetector().setEnabled(true);
        }
    }

}
