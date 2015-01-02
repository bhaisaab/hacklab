require 'date'
require 'net/smtp'

class BookingsController < ApplicationController

  def root
  end

  def about
  end

  def list
    @bookings = Booking.all
  end

  # GET /email?emails=zzz&user_id=xxx&booking_id=yyy
  def email
    @user = User.find(params[:user_id])
    @booking = Booking.find(params[:booking_id])
    
    message = <<MSG
From: batch9@baagi.org
To: #{params[:emails]}
Subject: FastConfBooking

Hi, You've a meeting: http://bc.baagi.org/bookings/#{@booking.id}
Cheers!
MSG
    Net::SMTP.start('localhost') do |smtp|
      smtp.send_message message, 'bhaisaab@baagi.org', params[:emails].split(',')
    end

  end

  # GET /bookings
  # GET /bookings.json
  def index
    year = Integer(params[:booking]['date(1i)'])
    month = Integer(params[:booking]['date(2i)'])
    day = Integer(params[:booking]['date(3i)'])

    #duration = params[:duration]
    capacity = params[:capacity]
    @requested_date = Date.new(year, month, day)
    @user = User.find(params[:user])
    @rooms = Room.all(:conditions => ["capacity >= :capacity", {:capacity => params[:capacity]}])
    @bookings = Booking.all
    respond_to do |format|
      format.html # index.html.erb
      format.json { render :json => @bookings }
    end
  end

  # GET /bookings/1
  # GET /bookings/1.json
  def show
    @booking = Booking.find(params[:id])
    respond_to do |format|
      format.html # show.html.erb
      format.json { render :json => @booking }
    end
  end

  # GET /bookings/new
  # GET /bookings/new.json
  def new
    @booking = Booking.new

    respond_to do |format|
      format.html # new.html.erb
      format.json { render :json => @booking }
    end
  end

  # GET /bookings/1/edit
  def edit
    @booking = Booking.find(params[:id])
  end

  # POST /bookings
  # POST /bookings.json
  def create
    @booking = Booking.new(params[:booking])
    print @booking
    @booking.slots.reject! { |c| c.empty? }
    print @booking.slots
    respond_to do |format|
      if @booking.save
        format.html { redirect_to @booking, :notice => 'Booking was successfully created.' }
        format.json { render :json => @booking, :status => :created, :location => @booking }
      else
        format.html { render :action => "new" }
        format.json { render :json => @booking.errors, :status => :unprocessable_entity }
      end
    end
  end

  # PUT /bookings/1
  # PUT /bookings/1.json
  def update
    @booking = Booking.find(params[:id])

    respond_to do |format|
      if @booking.update_attributes(params[:booking])
        format.html { redirect_to @booking, :notice => 'Booking was successfully updated.' }
        format.json { head :no_content }
      else
        format.html { render :action => "edit" }
        format.json { render :json => @booking.errors, :status => :unprocessable_entity }
      end
    end
  end

  # DELETE /bookings/1
  # DELETE /bookings/1.json
  def destroy
    @booking = Booking.find(params[:id])
    @booking.destroy

    respond_to do |format|
      format.html { redirect_to '/' }
      format.json { head :no_content }
    end
  end
end

