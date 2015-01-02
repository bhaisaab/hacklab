class Booking < ActiveRecord::Base
  attr_accessible :date, :room_id, :slots, :user_id

  validates :date,  :presence => true
  validates :slots,  :presence => true

  serialize :slots, Array

  belongs_to :user
  belongs_to :room

end
