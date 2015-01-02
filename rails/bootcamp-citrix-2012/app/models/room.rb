class Room < ActiveRecord::Base
  attr_accessible :building, :capacity, :floor, :name

  validates_uniqueness_of :name

  validates :name,  :presence => true
  validates :capacity,  :presence => true
  validates :floor,  :presence => true
  validates :building,  :presence => true

  has_many :bookings, :dependent => :destroy

end
