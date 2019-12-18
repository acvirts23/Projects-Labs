from konane import *


class MinimaxPlayer(Konane, Player):

	def __init__(self, size, depthLimit):
		Konane.__init__(self, size)
		self.limit = depthLimit
		depth = self.limit


	def initialize(self, side):
		self.side = side
		self.name = "MiniPlayer"


	def minP(self, depth, board):
		#Generates a list of moves for MinPlayer
		moves = self.generateMoves(board, self.opponent(self.side))

		if depth == 0:
			self.eval(board)

		elif moves == []:
			#No more moves left
			return float("inf")

		
		else: 
			value = float("inf")
			for move in moves:
				newBoard = self.nextBoard(board, self.opponent(self.side), move)
				value = self.maxP(depth-1, newBoard)
			return value





	def maxP(self, depth, board):
		moves = self.generateMoves(board, self.opponent(self.side))

		if depth == 0:
			self.eval(board)

		elif moves == []:
			return -float("inf")

		else:
			value = -float("inf")
			for move in moves:
				newBoard = self.nextBoard(board, self.side, move)
				value = self.minP(self.limit-1, newBoard)

			return value


	def getMove(self, board):
		moves = self.generateMoves(board, self.side)
		n = len(moves)
		if n == 0:
			return []

		lastval = -float("infinity")
		bestMove = []

		for move in moves:
			newBoard = self.nextBoard(board, self.side, move)
			val = self.minP(self.limit-1, newBoard)
			if (val >= lastval):
				lastval = val
				bestMove = move

		return bestMove            
		#call minimax as minimizing player, loops takes highest value.
		#alternate calls between max and min
		#get move is where that decision happens, call next board,
		#and then call min player with the new board.
		#return move corresponding to highest number

	def eval(self, board):
		#TODO, eval function high values are good for max, return high number for max
		#low number if bad for max (max is self)
		#if no moves left or max depth, return a value
		numMoves = len(self.generateMoves(board, self))
		if numMoves == 0:
			return -float("inf")

		selfMoves = board.getMove(self, board)
		selfScore = numMoves * 4 + selfMoves

		numOpponentMoves = len(self.generateMoves(board, self.opponent(self.side)))
		if numOpponentMoves == 0:
			return float("inf")

		oppMoves = board.getMove(self, board)
		oppScore = numOpponentMoves * 4 + oppMoves

		score = selfScore - oppScore
		return score
