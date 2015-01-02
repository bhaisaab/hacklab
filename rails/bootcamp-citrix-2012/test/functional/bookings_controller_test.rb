require 'test_helper'

class BookingsControllerTest < ActionController::TestCase
  setup do
    @booking = bookings(:one)
  end

  test "should get index" do
    get :index
    assert_response :success
    assert_not_nil assigns(:bookings)
  end

  test "should get new" do
    get :new
    assert_response :success
  end

  test "should create booking" do
    assert_difference('Booking.count') do
      post :create, :booking => { :date => @booking.date, :room_id => @booking.room_id, :slots => @booking.slots, :user_id => @booking.user_id }
    end

    assert_redirected_to booking_path(assigns(:booking))
  end

  test "should show booking" do
    get :show, :id => @booking
    assert_response :success
  end

  test "should get edit" do
    get :edit, :id => @booking
    assert_response :success
  end

  test "should update booking" do
    put :update, :id => @booking, :booking => { :date => @booking.date, :room_id => @booking.room_id, :slots => @booking.slots, :user_id => @booking.user_id }
    assert_redirected_to booking_path(assigns(:booking))
  end

  test "should destroy booking" do
    assert_difference('Booking.count', -1) do
      delete :destroy, :id => @booking
    end

    assert_redirected_to bookings_path
  end
end
